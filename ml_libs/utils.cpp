// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _ML_UTILS
#define _ML_UTILS

#include <chrono>
#include <vector>
#include <torch/torch.h>
#include <optional>
using namespace std;
using torch::Tensor;
using torch::TensorOptions;

double default_timer()
{
    // 返回以秒为单位的浮点数.
    chrono::time_point t = chrono::system_clock::now();
    chrono::system_clock::duration dtn = t.time_since_epoch();
    return dtn.count() % int64_t(1e15) / 1e9; // 避免浮点数精度问题.
}

template <class T>
void test_time(function<void(T &)> func, T &res, int number = 1, int warm_up = 0,
               function<double()> timer = nullptr)
{
    // func: 传入的参数为res.
    // 使用: test_time<Tensor>(func, y, 100, 0, time_synchronize);
    if (timer == nullptr)
    {
        timer = default_timer;
    }

    vector<double> ts;
    for (int _ = 0; _ < warm_up; ++_)
    {
        func(res);
    }
    for (int _ = 0; _ < number; ++_)
    {
        double t = timer();
        func(res);
        ts.push_back(timer() - t);
    }
    // double
    Tensor ts_t = torch::from_blob(ts.data(), {int(ts.size())}, TensorOptions().dtype(torch::kDouble));
    double mean = ts_t.mean().item<double>();
    double std = number > 1 ? ts_t.std().item<double>() : 0;
    double max = ts_t.max().item<double>();
    double min = ts_t.min().item<double>();
    printf("time[number=%d]: %.6f±%.6f |max: %.6f |min: %.6f\n", number, mean, std, max, min);
}

// void func(int &res)
// {
//     res = 1;
//     usleep(int(1e6));
// }

// int main()
// {
//     int res;
//     test_time<int>(func, res, 1, 0, default_timer);
// }

template <class T>
void tensor_to_vector(Tensor &t, vector<T> &dst)
{
    // copy
    dst.assign(t.data_ptr<T>(), t.data_ptr<T>() + t.numel());
}

// int main()
// {
//     Tensor t = torch::randn({10000});
//     vector<float> v;
//     tensor_to_vector(t, v);
//     cout << t[0] << '\n';
//     t[0] = 100;
//     cout << t[0] << '\n';
//     cout << v[0];
// }

double time_synchronize()
{
    torch::cuda::synchronize();
    return default_timer();
}

int64_t seed_everything(optional<int64_t> seed = nullopt, bool gpu_dtm = false)
{
    if (seed == nullopt)
    {
        seed = torch::randint(0, UINT32_MAX).item<int64_t>();
    }
    torch::manual_seed(seed.value());
    torch::cuda::manual_seed_all(seed.value());
    // https://discuss.pytorch.org/t/libtorch-sequential-model-is-not-consistent-with-pytorch-sequential-model/153556/3
    if (gpu_dtm)
    {
        // torch::globalContext().setDeterministicAlgorithms(true, false);  // 会报错
        torch::globalContext().setDeterministicCuDNN(true);
        torch::globalContext().setBenchmarkCuDNN(false);
    }
    cout << "Global seed set to " << seed.value() << '\n';
    return seed.value();
}

// int main(){
//     seed_everything(3234335211);
//     Tensor x =  torch::randn({10000, 10000}, TensorOptions().device(torch::kCUDA));
//     auto func = [&x](Tensor &res)->void{
//         res = x.matmul(x);
//     };
//     Tensor y;
//     test_time<Tensor>(func, y, 10, 0, time_synchronize);
//     cout << y.index({1, Slice(None, 100)});
// }

#endif