#ifndef PQCLEAN_HQC128_CLEAN_REED_SOLOMON_H
#define PQCLEAN_HQC128_CLEAN_REED_SOLOMON_H

/**
 * @file reed_solomon.h
 * @brief Header file of reed_solomon.c
 */

#include "parameters.h"
#include <stddef.h>
#include <stdint.h>

static const uint16_t alpha_ij_pow[30][45] = {{2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193}, {4, 16, 64, 29, 116, 205, 19, 76, 45, 180, 234, 143, 6, 24, 96, 157, 78, 37, 148, 106, 181, 238, 159, 70, 5, 20, 80, 93, 105, 185, 222, 95, 97, 153, 94, 101, 137, 30, 120, 253, 211, 107, 177, 254, 223}, {8, 64, 58, 205, 38, 45, 117, 143, 12, 96, 39, 37, 53, 181, 193, 70, 10, 80, 186, 185, 161, 97, 47, 101, 15, 120, 231, 107, 127, 223, 182, 217, 134, 68, 26, 208, 206, 62, 237, 59, 197, 102, 23, 184, 169}, {16, 29, 205, 76, 180, 143, 24, 157, 37, 106, 238, 70, 20, 93, 185, 95, 153, 101, 30, 253, 107, 254, 91, 217, 17, 13, 208, 129, 248, 59, 151, 133, 184, 79, 132, 168, 82, 73, 228, 230, 198, 252, 123, 227, 150}, {32, 116, 38, 180, 3, 96, 156, 106, 193, 5, 160, 185, 190, 94, 15, 253, 214, 223, 226, 17, 26, 103, 124, 59, 51, 46, 169, 132, 77, 85, 114, 230, 145, 215, 255, 150, 55, 174, 100, 28, 167, 89, 239, 172, 36}, {64, 205, 45, 143, 96, 37, 181, 70, 80, 185, 97, 101, 120, 107, 223, 217, 68, 208, 62, 59, 102, 184, 33, 168, 85, 228, 191, 252, 241, 150, 110, 130, 7, 221, 89, 195, 138, 61, 251, 44, 207, 173, 8, 58, 38}, {128, 19, 117, 24, 156, 181, 140, 93, 161, 94, 60, 107, 163, 67, 26, 129, 147, 102, 109, 132, 41, 57, 209, 252, 255, 98, 87, 200, 224, 89, 155, 18, 245, 11, 233, 173, 16, 232, 45, 3, 157, 53, 159, 40, 185}, {29, 76, 143, 157, 106, 70, 93, 95, 101, 253, 254, 217, 13, 129, 59, 133, 79, 168, 73, 230, 252, 227, 149, 130, 28, 81, 195, 18, 247, 44, 27, 2, 58, 152, 3, 39, 212, 140, 186, 190, 202, 231, 225, 175, 26}, {58, 45, 12, 37, 193, 80, 161, 101, 231, 223, 134, 208, 237, 102, 169, 168, 146, 191, 179, 150, 87, 7, 166, 195, 36, 251, 125, 173, 64, 38, 143, 39, 181, 10, 185, 47, 120, 127, 217, 26, 62, 197, 184, 21, 85}, {116, 180, 96, 106, 5, 185, 94, 253, 223, 17, 103, 59, 46, 132, 85, 230, 215, 150, 174, 28, 89, 172, 244, 44, 108, 32, 38, 3, 156, 193, 160, 190, 15, 214, 226, 26, 124, 51, 169, 77, 114, 145, 255, 55, 100}, {232, 234, 39, 238, 160, 97, 60, 254, 134, 103, 118, 184, 84, 57, 145, 227, 220, 7, 162, 172, 245, 176, 71, 58, 180, 192, 181, 40, 95, 15, 177, 175, 208, 147, 46, 21, 73, 99, 241, 55, 200, 166, 43, 122, 44}, {205, 143, 37, 70, 185, 101, 107, 217, 208, 59, 184, 168, 228, 252, 150, 130, 221, 195, 61, 44, 173, 58, 117, 39, 193, 186, 47, 231, 182, 26, 237, 23, 21, 146, 145, 219, 87, 56, 242, 36, 139, 54, 64, 45, 96}, {135, 6, 53, 20, 190, 120, 163, 13, 237, 46, 84, 228, 229, 98, 100, 81, 69, 251, 131, 32, 45, 192, 238, 186, 94, 187, 217, 189, 236, 169, 82, 209, 241, 220, 28, 242, 72, 22, 173, 116, 201, 37, 140, 222, 15}, {19, 24, 181, 93, 94, 107, 67, 129, 102, 132, 57, 252, 98, 200, 89, 18, 11, 173, 232, 3, 53, 40, 194, 231, 226, 189, 197, 158, 170, 145, 75, 25, 166, 69, 235, 54, 29, 234, 37, 5, 95, 120, 91, 52, 59}, {38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145, 150, 100, 89, 36, 44, 1, 38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145, 150, 100, 89, 36, 44, 1, 38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145}, {76, 157, 70, 95, 253, 217, 129, 133, 168, 230, 227, 130, 81, 18, 44, 2, 152, 39, 140, 190, 231, 175, 31, 23, 77, 209, 219, 25, 162, 36, 88, 4, 45, 78, 5, 97, 211, 67, 62, 46, 154, 191, 171, 50, 89}, {152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1, 152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1, 152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1}, {45, 37, 80, 101, 223, 208, 102, 168, 191, 150, 7, 195, 251, 173, 38, 39, 10, 47, 127, 26, 197, 21, 115, 219, 100, 242, 245, 54, 205, 96, 70, 97, 107, 68, 59, 33, 228, 241, 130, 89, 61, 207, 58, 12, 193}, {90, 148, 186, 30, 226, 62, 109, 73, 179, 174, 162, 61, 131, 232, 96, 140, 153, 127, 52, 51, 168, 99, 98, 56, 172, 22, 8, 234, 212, 185, 240, 67, 237, 79, 114, 241, 25, 121, 245, 108, 19, 39, 20, 188, 223}, {180, 106, 185, 253, 17, 59, 132, 230, 150, 28, 172, 44, 32, 3, 193, 190, 214, 26, 51, 77, 145, 55, 167, 36, 233, 116, 96, 5, 94, 223, 103, 46, 85, 215, 174, 89, 244, 108, 38, 156, 160, 15, 226, 124, 169}, {117, 181, 161, 107, 26, 102, 41, 252, 87, 89, 245, 173, 45, 53, 185, 231, 68, 197, 168, 145, 110, 166, 61, 54, 38, 37, 186, 120, 134, 59, 21, 191, 196, 221, 36, 207, 205, 39, 80, 15, 217, 237, 33, 115, 150}, {234, 238, 97, 254, 103, 184, 57, 227, 7, 172, 176, 58, 192, 40, 15, 175, 147, 21, 99, 55, 166, 122, 216, 45, 106, 222, 107, 52, 133, 85, 123, 50, 195, 11, 32, 12, 140, 188, 182, 124, 158, 115, 49, 224, 36}, {201, 159, 47, 91, 124, 33, 209, 149, 166, 244, 71, 117, 238, 194, 223, 31, 79, 115, 98, 167, 61, 216, 90, 181, 190, 254, 206, 218, 213, 150, 224, 72, 54, 152, 106, 161, 177, 189, 184, 114, 171, 56, 18, 131, 38}, {143, 70, 101, 217, 59, 168, 252, 130, 195, 44, 58, 39, 186, 231, 26, 23, 146, 219, 56, 36, 54, 45, 181, 97, 223, 62, 33, 191, 110, 89, 251, 8, 12, 10, 15, 134, 197, 41, 179, 100, 86, 125, 205, 37, 185}, {3, 5, 15, 17, 51, 85, 255, 28, 36, 108, 180, 193, 94, 226, 59, 77, 215, 100, 172, 233, 38, 106, 190, 223, 124, 132, 145, 174, 239, 44, 116, 156, 185, 214, 103, 169, 230, 55, 89, 235, 32, 96, 160, 253, 26}, {6, 20, 120, 13, 46, 228, 98, 81, 251, 32, 192, 186, 187, 189, 169, 209, 220, 242, 22, 116, 37, 222, 254, 62, 132, 63, 130, 43, 250, 38, 212, 194, 182, 147, 77, 179, 141, 9, 54, 180, 159, 101, 67, 151, 85}, {12, 80, 231, 208, 169, 191, 87, 195, 125, 38, 181, 47, 217, 197, 85, 219, 221, 245, 8, 96, 186, 107, 206, 33, 145, 130, 86, 207, 45, 193, 101, 134, 102, 146, 150, 166, 251, 64, 39, 185, 127, 62, 21, 252, 100}, {24, 93, 107, 129, 132, 252, 200, 18, 173, 3, 40, 231, 189, 158, 145, 25, 69, 54, 234, 5, 120, 52, 218, 191, 174, 43, 207, 90, 35, 15, 136, 92, 115, 220, 239, 125, 76, 238, 101, 17, 133, 228, 149, 121, 44}, {48, 105, 127, 248, 77, 241, 224, 247, 64, 156, 95, 182, 236, 170, 150, 162, 11, 205, 212, 94, 134, 133, 213, 110, 239, 250, 45, 35, 30, 26, 218, 99, 130, 69, 108, 143, 40, 211, 206, 132, 229, 7, 144, 2, 96}, {96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15, 26, 169, 145, 100, 36, 1, 96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15, 26, 169, 145, 100, 36, 1, 96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15}};

void PQCLEAN_HQC128_CLEAN_reed_solomon_encode(uint8_t *cdw, const uint8_t *msg);

void PQCLEAN_HQC128_CLEAN_reed_solomon_decode(uint8_t *msg, uint8_t *cdw);

#endif
