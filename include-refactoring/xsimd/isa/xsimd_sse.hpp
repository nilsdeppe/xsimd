#ifndef XSIMD_SSE_HPP
#define XSIMD_SSE_HPP

#include "../types/xsimd_sse_register.hpp"


namespace xsimd {

  namespace kernel {
    using namespace types;

    // abs
    template<class A> batch<float, A> abs(batch<float, A> const& self, requires<sse>) {
      __m128 sign_mask = _mm_set1_ps(-0.f);  // -0.f = 1 << 31
      return _mm_andnot_ps(sign_mask, self);
    }
    template<class A> batch<double, A> abs(batch<double, A> const& self, requires<sse>) {
      __m128d sign_mask = _mm_set1_pd(-0.f);  // -0.f = 1 << 31
      return _mm_andnot_pd(sign_mask, self);
    }

    // add
    template<class A> batch<float, A> add(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_add_ps(self, other);
    }
    template<class A> batch<double, A> add(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_add_pd(self, other);
    }

    // bitwise_and
    template<class A> batch<float, A> bitwise_and(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_and_ps(self, other);
    }
    template<class A> batch<double, A> bitwise_and(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_and_pd(self, other);
    }


    // bitwise_not
    template<class A> batch<float, A> bitwise_not(batch<float, A> const& self, requires<sse>) {
      return _mm_xor_ps(self, _mm_castsi128_ps(_mm_set1_epi32(-1)));
    }
    template <class A>
    batch<double, A> bitwise_not(batch<double, A> const &self, requires<sse>) {
      return _mm_xor_pd(self, _mm_castsi128_pd(_mm_set1_epi32(-1)));
    }

    // broadcast
    template<class A> batch<float, A> broadcast(float val, requires<sse>) {
      return _mm_set_ps(val, val, val, val);
    }
    template<class A> batch<double, A> broadcast(double val, requires<sse>) {
      return _mm_set_pd(val, val);
    }

    // div
    template<class A> batch<float, A> div(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_div_ps(self, other);
    }
    template<class A> batch<double, A> div(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_div_pd(self, other);
    }

    // eq
    template<class A> batch_bool<float, A> eq(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmpeq_ps(self, other);
    }
    template<class A> batch_bool<double, A> eq(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmpeq_pd(self, other);
    }

    // ge
    template<class A> batch_bool<float, A> ge(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmpge_ps(self, other);
    }
    template<class A> batch_bool<double, A> ge(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmpge_pd(self, other);
    }

    // gt
    template<class A> batch_bool<float, A> gt(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmpgt_ps(self, other);
    }
    template<class A> batch_bool<double, A> gt(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmpgt_pd(self, other);
    }

    // hadd
    template<class A> float hadd(batch<float, A> const& self, requires<sse>) {
      __m128 tmp0 = _mm_add_ps(self, _mm_movehl_ps(self, self));
      __m128 tmp1 = _mm_add_ss(tmp0, _mm_shuffle_ps(tmp0, tmp0, 1));
      return _mm_cvtss_f32(tmp1);
    }
    template <class A>
    double hadd(batch<double, A> const &self, requires<sse>) {
      return _mm_cvtsd_f64(_mm_add_sd(self, _mm_unpackhi_pd(self, self)));
    }

    // haddp
    template<class A> batch<float, A> haddp(batch<float, A> const* row, requires<sse>) {
      __m128 tmp0 = _mm_unpacklo_ps(row[0], row[1]);
      __m128 tmp1 = _mm_unpackhi_ps(row[0], row[1]);
      __m128 tmp2 = _mm_unpackhi_ps(row[2], row[3]);
      tmp0 = _mm_add_ps(tmp0, tmp1);
      tmp1 = _mm_unpacklo_ps(row[2], row[3]);
      tmp1 = _mm_add_ps(tmp1, tmp2);
      tmp2 = _mm_movehl_ps(tmp1, tmp0);
      tmp0 = _mm_movelh_ps(tmp0, tmp1);
      return _mm_add_ps(tmp0, tmp2);
    }
    template <class A>
    batch<double, A> haddp(batch<double, A> const *row, requires<sse>) {
      return _mm_add_pd(_mm_unpacklo_pd(row[0], row[1]),
          _mm_unpackhi_pd(row[0], row[1]));
    }

    // le
    template<class A> batch_bool<float, A> le(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmple_ps(self, other);
    }
    template<class A> batch_bool<double, A> le(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmple_pd(self, other);
    }

    // load_aligned
    template<class A> batch<float, A> load_aligned(float const* mem, convert<float>, requires<sse>) {
      return _mm_load_ps(mem);
    }
    template<class A> batch<double, A> load_aligned(double const* mem, convert<double>, requires<sse>) {
      return _mm_load_pd(mem);
    }

    // load_unaligned
    template<class A> batch<float, A> load_unaligned(float const* mem, convert<float>, requires<sse>){
      return _mm_loadu_ps(mem);
    }
    template<class A> batch<double, A> load_unaligned(double const* mem, convert<double>, requires<sse>){
      return _mm_loadu_pd(mem);
    }

    // lt
    template<class A> batch_bool<float, A> lt(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmplt_ps(self, other);
    }
    template<class A> batch_bool<double, A> lt(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmplt_pd(self, other);
    }

    // max
    template<class A> batch<float, A> max(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_max_ps(self, other);
    }
    template<class A> batch<double, A> max(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_max_pd(self, other);
    }

    // min
    template<class A> batch<float, A> min(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_min_ps(self, other);
    }
    template<class A> batch<double, A> min(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_min_pd(self, other);
    }

    // mul
    template<class A> batch<float, A> mul(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_mul_ps(self, other);
    }
    template<class A> batch<double, A> mul(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_mul_pd(self, other);
    }

    // neg
    template<class A> batch<float, A> neg(batch<float, A> const& self, requires<sse>) {
      return _mm_xor_ps(self, _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
    }
    template <class A>
    batch<double, A> neg(batch<double, A> const &self, requires<sse>) {
      return _mm_xor_pd(
          self, _mm_castsi128_pd(_mm_setr_epi32(0, 0x80000000, 0, 0x80000000)));
    }

    // neq
    template<class A> batch_bool<float, A> neq(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_cmpneq_ps(self, other);
    }
    template<class A> batch_bool<double, A> neq(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_cmpneq_pd(self, other);
    }

    // sadd
    template<class A> batch<float, A> sadd(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_add_ps(self, other); // no saturated arithmetic on floating point numbers
    }
    template<class A> batch<double, A> sadd(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_add_pd(self, other); // no saturated arithmetic on floating point numbers
    }

    // sqrt
    template<class A> batch<float, A> sqrt(batch<float, A> const& val, requires<sse>) {
      return _mm_sqrt_ps(val);
    }
    template<class A> batch<double, A> sqrt(batch<double, A> const& val, requires<sse>) {
      return _mm_sqrt_pd(val);
    }

    // ssub
    template<class A> batch<float, A> ssub(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_sub_ps(self, other); // no saturated arithmetic on floating point numbers
    }
    template<class A> batch<double, A> ssub(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_sub_pd(self, other); // no saturated arithmetic on floating point numbers
    }

    // store_aligned
    template<class A> void store_aligned(float *mem, batch<float, A> const& self, requires<sse>) {
      return _mm_store_ps(mem, self);
    }
    template<class A> void store_aligned(double *mem, batch<double, A> const& self, requires<sse>) {
      return _mm_store_pd(mem, self);
    }

    // store_unaligned
    template<class A> void store_unaligned(float *mem, batch<float, A> const& self, requires<sse>) {
      return _mm_storeu_ps(mem, self);
    }
    template<class A> void store_unaligned(double *mem, batch<double, A> const& self, requires<sse>) {
      return _mm_storeu_pd(mem, self);
    }

    // sub
    template<class A> batch<float, A> sub(batch<float, A> const& self, batch<float, A> const& other, requires<sse>) {
      return _mm_sub_ps(self, other);
    }
    template<class A> batch<double, A> sub(batch<double, A> const& self, batch<double, A> const& other, requires<sse>) {
      return _mm_sub_pd(self, other);
    }
  }

}

#endif