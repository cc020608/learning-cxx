#include "../exercise.h"

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        std::memcpy(shape, shape_, 4 * sizeof(unsigned int));
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查形状是否可广播
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && shape[i] != 1 && others.shape[i] != 1) {
                throw std::invalid_argument("Shapes are not broadcastable.");
            }
        }

        unsigned int total_size = 1;
        for (int i = 0; i < 4; ++i) {
            total_size *= std::max(shape[i], others.shape[i]);
        }

        for (unsigned int i = 0; i < total_size; ++i) {
            unsigned int this_idx = 0;
            unsigned int others_idx = 0;
            unsigned int this_stride = 1;
            unsigned int others_stride = 1;

            for (int j = 3; j >= 0; --j) {
                unsigned int this_dim = (shape[j] == 1) ? 0 : (i / this_stride) % shape[j];
                unsigned int others_dim = (others.shape[j] == 1) ? 0 : (i / others_stride) % others.shape[j];

                this_idx = this_idx * shape[j] + this_dim;
                others_idx = others_idx * others.shape[j] + others_dim;

                this_stride *= shape[j];
                others_stride *= others.shape[j];
            }

            data[this_idx] += others.data[others_idx];
        }

        return *this;
    }
};


// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(data) / sizeof(int); i++) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(d0) / sizeof(int); i++) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (unsigned int i = 0; i < sizeof(d0) / sizeof(int); i++) {
            ASSERT(t0.data[i] == t0.data[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
