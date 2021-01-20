// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef Float4_hpp
#define Float4_hpp
#include "tnn/core/macro.h"
#include "tnn/device/x86/x86_common.h"
namespace TNN_NS {

struct Float4 {
    __m128 value;
    Float4() {}
    Float4(const float v) {
        value = _mm_set1_ps(v);
    }
    Float4(const __m128& v) {
        value = v;
    }
    Float4(const __m128&& v) {
        value = std::move(v);
    }
    Float4(const Float4& lr) {
        value = lr.value;
    }
    Float4(const Float4&& lr) {
        value = std::move(lr.value);
    }

    // void set_lane(float v, int i) {
    //     value[i] = v;
    // }

    // const float operator[](const int i) const {
    //     return value[i];
    // }

    static Float4 load(const float* addr) {
        Float4 v;
        v.value = _mm_load_ps(addr);
        return v;
    }
    static Float4 loadu(const float* addr) {
        Float4 v;
        v.value = _mm_loadu_ps(addr);
        return v;
    }
    static void save(float* addr, const Float4& v) {
        _mm_store_ps(addr, v.value);
    }
    static void saveu(float* addr, const Float4& v) {
        _mm_storeu_ps(addr, v.value);
    }
    static void mla(Float4& v1, const Float4& v2, const Float4& v3) {
        v1.value = _mm_add_ps(v1.value, _mm_mul_ps(v2.value, v3.value));
    }
    static void mls(Float4& v1, const Float4& v2, const Float4& v3) {
        v1.value = _mm_sub_ps(v1.value, _mm_mul_ps(v2.value, v3.value));
    }
    static Float4 max(const Float4& v1, const Float4& v2) {
        Float4 dst;
        dst.value = _mm_max_ps(v1.value, v2.value);
        return dst;
    }
    static Float4 min(const Float4& v1, const Float4& v2) {
        Float4 dst;
        dst.value = _mm_min_ps(v1.value, v2.value);
        return dst;
    }
    Float4 operator+(const Float4& lr) {
        Float4 dst;
        dst.value = _mm_add_ps(value, lr.value);
        return dst;
    }
    Float4 operator-(const Float4& lr) {
        Float4 dst;
        dst.value = _mm_sub_ps(value, lr.value);
        return dst;
    }
    Float4 operator*(float lr) {
        Float4 dst;
        __m128 tmp = _mm_set1_ps(lr);
        dst.value = _mm_mul_ps(value, tmp);
        return dst;
    }
    Float4 operator*(const Float4& lr) {
        Float4 dst;
        dst.value = _mm_mul_ps(value, lr.value);
        return dst;
    }
    Float4& operator=(const Float4& lr) {
        value = lr.value;
        return *this;
    }
    Float4& operator=(const Float4&& lr) {
        value = std::move(lr.value);
        return *this;
    }
    Float4 operator-() {
        Float4 dst;
        dst.value = _mm_sub_ps(_mm_setzero_ps(), value);
        return dst;
    }
};

}  // namespace TNN_NS

#endif /* Float4_hpp */
