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

# ============= CountTree =============
cc_library(
    name = "CountTree",
    srcs = ["CountTree.cpp"],
    hdrs = [
        "CountTree.h",
        "CountTreeException.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@gtest//:main",
        ":utils",
        ":BigTree",
    ]
)

cc_test(
    name = "CountTreeTests",
    srcs = ["CountTree.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":CountTree",
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
        ":CountTree",
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
        ":CountTree",
    ]
)

# ============= PredictorCounter =============
cc_library(
    name = "PredictorCounter",
    srcs = ["PredictorCounter.cpp"],
    hdrs = ["PredictorCounter.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":CountTree",
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
        ":CountTree",
        ":Predictor",
        ":PredictorCounter",
    ]
)

# ============= optimize binary =============
cc_binary(
    name = "optimizer",
    srcs = ["optimizer.cpp", "OptimizerOptions.h"],
    copts = ["-std=c++11", "-Iexternal/gtest/include"],
    deps = [
        ":CountTree",
        ":Predictor",
        ":PredictorCounter",
        "@boost//:program_options",
    ],
    #data = [
    #    "//data:crackstation-human-only.txt",
    #],
)
