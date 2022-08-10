// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _NN_FUNCTIONAL
#define _NN_FUNCTIONAL

#include <torch/torch.h>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <optional>
#include "utils.cpp"

using torch::IntArrayRef;
using torch::Tensor;
using torch::TensorOptions;
using namespace torch::indexing;
using namespace std;
namespace F = torch::nn::functional;

// Tensor conv2d(
//     Tensor x,
//     Tensor weight,
//     const optional<Tensor> &bias = nullopt,
//     const tuple<int, int> &stride = {1, 1},
//     const tuple<int, int> &padding = {0, 0},
//     const int dilation = 1,
//     const int groups = 1)
// {
//     auto [PH, PW] = padding;
//     if (padding != tuple<int, int>({0, 0}))
//     {
//         auto options = F::PadFuncOptions({PW, PW, PH, PH});
//         x = F::pad(x, options); // lrtb
//     }
//     int Hin = x.size(2), Win = x.size(3);
//     int D = dilation, G = groups;
//     int KH = weight.size(2), KW = weight.size(3);
//     int KH_D = (KH - 1) * D + 1, KW_D = (KW - 1) * D + 1;
//     auto [SH, SW] = stride;
//     int N = x.size(0), Cin = x.size(1);
//     int Cout = weight.size(0);
//     assert(weight.size(1) * G == Cin);
//     int Hout = (Hin - KH_D) / SH + 1, Wout = (Win - KW_D) / SW + 1;
//     auto options = torch::TensorOptions().device(x.device()).dtype(x.dtype());
//     Tensor res = torch::empty({N, Cout, Hout, Wout}, options);
//     x = x.contiguous().view({N, G, Cin / G, Hin, Win});
//     weight = weight.contiguous().view({G, Cout / G, Cin / G, KH, KW});
//     for (int i = 0; i < Hout; ++i)
//     {
//         for (int j = 0; j < Wout; ++j)
//         {
//             int h_start = i * SH, w_start = j * SW;
//             Slice h_pos({h_start, h_start + KH_D, D}), w_pos({w_start, w_start + KW_D, D});
//             res.index_put_({Slice(), Slice(), i, j},
//                            torch::einsum("abcde,bfcde->abf",
//                                          {x.index({Slice(), Slice(), Slice(), h_pos, w_pos}), weight})
//                                .contiguous()
//                                .view({N, Cout}));
//         }
//     }
//     if (bias.has_value())
//     {
//         res.add_(bias.value().index({None, Slice(), None, None}));
//     }
//     return res;
// }

Tensor conv2d(
    Tensor x,
    Tensor weight,
    const optional<Tensor> &bias = nullopt,
    const tuple<int, int> &stride = {1, 1},
    const tuple<int, int> &padding = {0, 0},
    const int dilation = 1,
    const int groups = 1)
{
    auto [PH, PW] = padding;
    if (padding != tuple<int, int>({0, 0}))
    {
        auto options = F::PadFuncOptions({PW, PW, PH, PH});
        x = F::pad(x, options); // lrtb
    }
    int Hin = x.size(2), Win = x.size(3);
    int D = dilation, G = groups;
    int KH = weight.size(2), KW = weight.size(3);
    int KH_D = (KH - 1) * D + 1, KW_D = (KW - 1) * D + 1;
    auto [SH, SW] = stride;
    int N = x.size(0), Cin = x.size(1);
    int Cout = weight.size(0);
    assert(weight.size(1) * G == Cin);
    int Hout = (Hin - KH_D) / SH + 1, Wout = (Win - KW_D) / SW + 1;
    auto options = torch::TensorOptions().device(x.device()).dtype(x.dtype());
    vector<Tensor> vres;
    vres.reserve(Hout * Wout);
    x = x.contiguous().view({N, G, Cin / G, Hin, Win});
    weight = weight.contiguous().view({G, Cout / G, Cin / G, KH, KW});
    for (int i = 0; i < Hout; ++i)
    {
        for (int j = 0; j < Wout; ++j)
        {
            int h_start = i * SH, w_start = j * SW;
            Slice h_pos({h_start, h_start + KH_D, D}), w_pos({w_start, w_start + KW_D, D});
            vres.push_back(torch::einsum("abcde,bfcde->abf",
                                         {x.index({Slice(), Slice(), Slice(), h_pos, w_pos}), weight}));
        }
    }
    Tensor res = torch::stack(vres, -1).view({N, Cout, Hout, Wout});
    if (bias.has_value())
    {
        res.add_(bias.value().index({None, Slice(), None, None}));
    }
    return res;
}

// int main()
// {
//     {
//         seed_everything(42, true);
//         TensorOptions options = TensorOptions().device(torch::kCUDA).dtype(torch::kFloat32);
//         Tensor x = torch::randn({64, 128, 112, 112}, options);
//         Tensor w = torch::randn({256, 128, 3, 3}, options);
//         Tensor b = torch::randn({256}, options);
//         F::Conv2dFuncOptions conv2doptions = F::Conv2dFuncOptions().bias(b).stride(1).padding(1).dilation(2).groups(1);
//         auto func = [&x, &w, &conv2doptions](Tensor &res)
//         {
//             res = F::conv2d(x, w, conv2doptions);
//         };
//         Tensor res, res2;
//         test_time<Tensor>(func, res, 10, 0, time_synchronize);
//         auto func2 = [&x, &w, &b](Tensor &res)
//         {
//             res = conv2d(x, w, b, {1, 1}, {1, 1}, 2, 1);
//         };
//         test_time<Tensor>(func2, res2, 10, 0, time_synchronize);
//         cout << torch::allclose(res, res2, 1e-4, 1e-3) << '\n';
//     }
//     // Global seed set to 42
//     // time[number=10]: 0.400687±0.181105 |max: 0.912719 |min: 0.301507
//     // time[number=10]: 0.066094±0.002316 |max: 0.072534 |min: 0.064735
//     // 1
//     {
//         seed_everything(42, true);
//         TensorOptions options = TensorOptions().device(torch::kCUDA).dtype(torch::kFloat32);
//         Tensor x = torch::randn({64, 128, 112, 112}, options);
//         Tensor w = torch::randn({256, 1, 3, 3}, options);
//         Tensor b = torch::randn({256}, options);
//         F::Conv2dFuncOptions conv2doptions = F::Conv2dFuncOptions().bias(b).stride(1).padding(1).dilation(2).groups(128);
//         auto func = [&x, &w, &conv2doptions](Tensor &res)
//         {
//             res = F::conv2d(x, w, conv2doptions);
//         };
//         Tensor res, res2;
//         test_time<Tensor>(func, res, 10, 0, time_synchronize);
//         auto func2 = [&x, &w, &b](Tensor &res)
//         {
//             res = conv2d(x, w, b, {1, 1}, {1, 1}, 2, 128);
//         };
//         test_time<Tensor>(func2, res2, 10, 0, time_synchronize);
//         cout << torch::allclose(res, res2, 1e-4, 1e-3) << '\n';
//     }
// }

#endif
