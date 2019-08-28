# ============= BigTree =============
cc_library(
    name = "BigTree",
    hdrs = [
        "BigTree.h",
        "BigTreeException.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":utils",
    ]
)

# ============= PTree =============
cc_library(
    name = "PTree",
    srcs = ["PTree.cpp"],
    hdrs = [
        "PTree.h",
        "PTreeException.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@gtest//:main",
        ":utils",
        ":BigTree",
    ]
)

cc_test(
    name = "PTreeTests",
    srcs = ["PTree.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":PTree",
    ]
)

# ============= utils =============
cc_library(
    name = "utils",
    srcs = ["utils.cpp"],
    hdrs = ["utils.h"],
)

cc_test(
    name = "UtilsTests",
    srcs = ["utils.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":utils",
    ]
)

# ============= Predictor =============
cc_library(
    name = "Predictor",
    srcs = ["Predictor.cpp"],
    hdrs = ["Predictor.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":BigTree",
        ":PTree",
        "@boost//:serialization",
        "@boost//:iostreams",
    ]
)

cc_test(
    name = "PredictorTests",
    srcs = ["Predictor.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":Predictor",
        ":PTree",
    ]
)

# ============= PredictorCounter =============
cc_library(
    name = "PredictorCounter",
    srcs = ["PredictorCounter.cpp"],
    hdrs = ["PredictorCounter.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":PTree",
        ":Predictor",
        "@boost//:multiprecision",
    ]
)

cc_test(
    name = "PredictorCounterTests",
    srcs = ["Predictor.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":PTree",
        ":Predictor",
        ":PredictorCounter",
    ]
)

# ============= main =============
cc_binary(
    name = "optimizer",
    srcs = ["optimizer.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":Predictor",
        ":PredictorCounter",
    ],
)
