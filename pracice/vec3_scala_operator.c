/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scala_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:38:40 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/21 15:14:58 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 multiply_scalar_vec3(double t, t_vec3 v) {
    t_vec3 result;

    result.e[0] = t * v.e[0];
    result.e[1] = t * v.e[1];
    result.e[2] = t * v.e[2];
    return result;
}
t_vec3 vmin(t_vec3 a, t_vec3 b) {
    t_vec3 result;
    result.e[0] = (a.e[0] < b.e[0]) ? a.e[0] : b.e[0];
    result.e[1] = (a.e[1] < b.e[1]) ? a.e[1] : b.e[1];
    result.e[2] = (a.e[2] < b.e[2]) ? a.e[2] : b.e[2];
    return result;
}

t_vec3  vec3_multiply_vec3(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;

    result.e[0] = v1.e[0] * v2.e[0];
    result.e[1] = v1.e[1] * v2.e[1];
    result.e[2] = v1.e[2] * v2.e[2];
    return (result);
}

// 벡터와 스칼라의 곱셈 (순서 바꾸어도 동일한 결과)
t_vec3 multiply_vec3_scalar(t_vec3 v, double t) {
    return multiply_scalar_vec3(t, v); // 이전 함수 재활용
}

// 벡터를 스칼라로 나누기
t_vec3 divide_vec3_scalar(t_vec3* v, double t) {
    t_vec3 result;
    double inv_t = 1.0 / t; // 스칼라를 역수로 계산
    result.e[0] = v->e[0] * inv_t;
    result.e[1] = v->e[1] * inv_t;
    result.e[2] = v->e[2] * inv_t;
    return result;
}

// 벡터 내적 (dot product) 계산
double dot_product(t_vec3* u, t_vec3* v) {
    return u->e[0] * v->e[0] + u->e[1] * v->e[1] + u->e[2] * v->e[2];
}

// 벡터 외적 (cross product) 계산
t_vec3 cross_product(t_vec3* u, t_vec3* v) {
    t_vec3 result;
    result.e[0] = u->e[1] * v->e[2] - u->e[2] * v->e[1];
    result.e[1] = u->e[2] * v->e[0] - u->e[0] * v->e[2];
    result.e[2] = u->e[0] * v->e[1] - u->e[1] * v->e[0];
    return result;
}

// 벡터를 단위 벡터로 정규화
t_vec3 normalize_vec3(t_vec3* v) {
    double length = sqrt(v->e[0] * v->e[0] + v->e[1] * v->e[1] + v->e[2] * v->e[2]);
    return divide_vec3_scalar(v, length);
}
