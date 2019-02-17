"""
Verify the metadata specified in the META.yml files.
"""

import copy
import itertools
import os
import pqclean
import yaml
import unittest

def test_metadata():
    for scheme in pqclean.Scheme.all_schemes():
        yield check_metadata, scheme.name

def check_metadata(scheme_name):
    scheme = pqclean.Scheme.by_name(scheme_name)
    metadata = scheme.metadata()

    specification = EXPECTED_FIELDS.items()

    if scheme.type == 'kem':
        specification = itertools.chain(specification, KEM_FIELDS.items())
    elif scheme.type == 'sign':
        specification = itertools.chain(specification, SIGNATURE_FIELDS.items())
    else:
        assert(False)

    check_spec(copy.deepcopy(metadata), specification)

    implementation_names_in_yaml = set(i['name'] for i in metadata['implementations'])
    implementations_on_disk = set(i.name for i in scheme.implementations)
    if implementation_names_in_yaml != implementations_on_disk:
        raise AssertionError("Implementations in YAML file {} and implementations on disk {} do not match"
            .format(implementation_names_in_yaml, implementations_on_disk))

EXPECTED_FIELDS = {
    'name': {'type': str},
    'type': {'type': str},
    'claimed-nist-level': {'type': int, 'min': 1, 'max': 5},
    'length-public-key': {'type': int, 'min': 1},
    'testvectors-sha256': {'type': str, 'length': 64},
    'principal-submitter': {'type': str},
    'auxiliary-submitters': {'type': list, 'elements': {'type': str}},
    'implementations': {
        'type': list,
        'elements': {
            'type': dict,
            'spec': {
                'name': {'type': str},
                'version': {'type': str},
            },
        },
    },
}

KEM_FIELDS = {
    'length-ciphertext': {'type': int, 'min': 1},
}

SIGNATURE_FIELDS = {
    'length-signature': {'type': int, 'min': 1},
}

def check_spec(metadata, spec):
    for field, props in spec:
        if field not in metadata:
            raise AssertionError("Field '{}' not present.".format(field))

        # validate element
        check_element(field, metadata[field], props)

        # delete it to detect extras
        del metadata[field]

    # Done checking all specified fields, check if we have extras
    for field, value in metadata.items():
        raise AssertionError("Unexpected item '{}' with value '{}'".format(field, value))


def check_element(field, element, props):
    type_ = props['type']
    # Validate type of element
    type_(element)

    # Strs are valid lists otherwise
    if type_ == list and type(element) != list:
        raise ValueError("Field {} not a list".format(field))

    # lists are valid dicts otherwise
    if type_ == dict and type(element) != dict:
        raise ValueError("Field {} not a dict".format(field))

    if type_ == int:
        element = int(element)
        if 'min' in props:
            if element < props['min']:
                raise ValueError("Value of field '{}' is lower than minimum "
                       "value {}".format(field, props['min']))
        if 'max' in props:
            if element > props['max']:
                raise ValueError("Value of field '{}' is larger than maximum"
                       " value {}".format(field, metafile, props['max']))

    if type_ == str:
        if 'length' in props:
            actual_len = len(element)
            if actual_len != props['length']:
                raise ValueError("Value of field '{}' should be length {}"
                       " but was length {}"
                       .format(field, props['length'], actual_len))

    if type_ == list:  # recursively check the elements
        for el in element:
            check_element('element of {}'.format(field), el, props['elements'])

    if type_ == dict:
        check_spec(element, props['spec'].items())