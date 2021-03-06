/* Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#ifdef PADDLE_WITH_XPU
#include "paddle/fluid/operators/elementwise/elementwise_add_op.h"
#include <memory>
#include <string>
#include "paddle/fluid/operators/elementwise/elementwise_op.h"

#include "paddle/fluid/operators/elementwise/elementwise_xpu.h"

namespace paddle {
namespace operators {

template <typename DeviceContext, typename T>
class ElementwiseAddXPUKernel : public framework::OpKernel<T> {
 public:
  void Compute(const framework::ExecutionContext &ctx) const override {
    XPUElementwise<T>(ctx, xpu::add<T>);
  }
};

template <typename DeviceContext, typename T>
class ElementwiseAddGradXPUKernel : public ElemwiseGradKernel<T> {
 public:
  void Compute(const framework::ExecutionContext &ctx) const override {
    ElemwiseGradKernel<T>::Compute(ctx);
    XPUElementwiseGrad<T>(ctx, xpu::add_grad<T>, false);
  }
};

}  // namespace operators
}  // namespace paddle

namespace ops = paddle::operators;

REGISTER_OP_XPU_KERNEL(
    elementwise_add,
    ops::ElementwiseAddXPUKernel<paddle::platform::XPUDeviceContext, float>);
REGISTER_OP_XPU_KERNEL(elementwise_add_grad,
                       ops::ElementwiseAddGradXPUKernel<
                           paddle::platform::XPUDeviceContext, float>);
#endif
