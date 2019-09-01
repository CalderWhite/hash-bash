cc_binary(
    name = "ingest_file",
    srcs = ["ingest_file.cpp"],
    deps = [
        "//optimizer:PTree",
        "//optimizer:Predictor",
    ],
    data = [
        "//data:crackstation-human-only.txt",
    ],
)

cc_binary(
    name = "get_offset",
    srcs = ["get_offset.cpp"],
    copts = ["-std=c++11", "-Iexternal/gtest/include"],
    deps = [
        "//optimizer:Predictor",
        "//optimizer:PredictorCounter",
        "@boost//:multiprecision",
    ],
    data = [
        "//data:crackstation-human-only.txt",
    ],
)
