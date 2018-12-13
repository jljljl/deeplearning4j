/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
//  @author raver119@gmail.com
//

#include <types/float16.h>
#include <dll.h>
#include <helpers/RandomLauncher.h>
#include <graph/RandomGenerator.h>
#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    // FIXME: implement this

    void RandomLauncher::applyDropOut(nd4j::graph::RandomGenerator& rng, NDArray *array, double retainProb, NDArray* z) {
        if (z == nullptr)
            z = array;

        auto extra = NDArrayFactory::create(retainProb);
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        //array->template applyRandom<randomOps::DropOut<T>>(buffer, nullptr, z, &retainProb);
        NativeOpExecutioner::execRandom(nullptr, random::DropOut, &rng, array->buffer(), array->shapeInfo(), z->buffer(), z->shapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::applyInvertedDropOut(nd4j::graph::RandomGenerator& rng, NDArray *array, double retainProb, NDArray* z) {
        if (z == nullptr)
            z = array;

        auto extra = NDArrayFactory::create(retainProb);
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        //array->template applyRandom<randomOps::DropOutInverted<T>>(buffer, nullptr, z, &retainProb);
        NativeOpExecutioner::execRandom(nullptr, random::DropOutInverted, &rng, array->buffer(), array->shapeInfo(), z->buffer(), z->shapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::applyAlphaDropOut(nd4j::graph::RandomGenerator& rng, NDArray *array, double retainProb, double alpha, double beta, double alphaPrime, NDArray* z) {
        if (z == nullptr)
            z = array;

        //  FIXME: this isn't portable code :(
        //T args[] = {retainProb, alpha, beta, alphaPrime};
        //nd4j::ops::alpha_dropout_bp op;
        //array->template applyRandom<randomOps::AlphaDropOut<T>>(buffer, nullptr, z, args);
        auto extra = NDArrayFactory::create(array->dataType(), {4}, {retainProb, alpha, beta, alphaPrime});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::AlphaDropOut, &rng, array->buffer(), array->shapeInfo(), z->buffer(), z->shapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillBernoulli(nd4j::graph::RandomGenerator& rng, NDArray* array, double prob) {
        auto extra = NDArrayFactory::create(prob);
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::BernoulliDistribution, &rng, array->buffer(), array->shapeInfo(), nullptr, nullptr, extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillUniform(nd4j::graph::RandomGenerator& rng, NDArray* array, double from, double to) {
        auto extra = NDArrayFactory::create(array->dataType(), {2}, {from, to});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        //array->template applyRandom<randomOps::UniformDistribution<T>>(buffer, nullptr, nullptr, args);
        NativeOpExecutioner::execRandom(nullptr, random::UniformDistribution, &rng, array->buffer(), array->shapeInfo(), nullptr, nullptr, extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillGaussian(nd4j::graph::RandomGenerator& rng, NDArray* array, double mean, double stdev) {
        auto extra = NDArrayFactory::create(array->dataType(), {2}, {mean, stdev});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::GaussianDistribution, &rng, array->buffer(), array->shapeInfo(), nullptr, nullptr, array->buffer(), array->shapeInfo(), nullptr, nullptr, array->buffer(), array->shapeInfo(), nullptr, nullptr, extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillExponential(nd4j::graph::RandomGenerator& rng, NDArray* array, double lambda) {
        auto extra = NDArrayFactory::create<double>(lambda);
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::ExponentialDistribution, &rng, array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillLogNormal(nd4j::graph::RandomGenerator& rng, NDArray* array, double mean, double stdev) {
        auto extra = NDArrayFactory::create(array->dataType(), {2}, {mean, stdev});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::GaussianDistribution, &rng, array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillTruncatedNormal(nd4j::graph::RandomGenerator& rng, NDArray* array, double mean, double stdev) {
        auto extra = NDArrayFactory::create(array->dataType(), {2}, {mean, stdev});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::TruncatedNormalDistribution, &rng, array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), extraPtr);


        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }

    void RandomLauncher::fillBinomial(nd4j::graph::RandomGenerator& rng, NDArray* array, int trials, double prob) {
        auto extra = NDArrayFactory::create(array->dataType(), {2}, {(double) trials, prob});
        auto extraPtr = extra.getBufferAsPointer(array->dataType());

        NativeOpExecutioner::execRandom(nullptr, random::BinomialDistributionEx, &rng, array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), array->buffer(), array->shapeInfo(), array->specialBuffer(), array->specialShapeInfo(), extraPtr);

        delete[] (reinterpret_cast<int8_t *>(extraPtr));
    }
}
