#ifndef SOURCEMETA_CORE_PREPROCESSOR_H_
#define SOURCEMETA_CORE_PREPROCESSOR_H_

#if defined(__GNUC__) || defined(__clang__)
#define SOURCEMETA_FORCEINLINE [[gnu::always_inline]]
#elifdef _MSC_VER
#define SOURCEMETA_FORCEINLINE [[msvc::forceinline]]
#else
#define SOURCEMETA_FORCEINLINE
#endif

#endif
