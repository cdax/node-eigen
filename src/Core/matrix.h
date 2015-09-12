#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#include <node.h>
#include <node_object_wrap.h>

#include <Eigen/Dense>

namespace eigen {

using node::ObjectWrap;

using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Value;
using v8::Object;
using v8::Persistent;
using v8::Function;

using Eigen::MatrixXd;
using Eigen::Dynamic;

class Matrix : public ObjectWrap {

    public:
        static void Init(Local<Object> exports);

    private:
        Matrix();
        Matrix(uint32_t rows);
        Matrix(uint32_t rows, uint32_t cols);
        ~Matrix();

        static void New(const FunctionCallbackInfo<Value>& args);

        static void Rows(const FunctionCallbackInfo<Value>& args);
        static void Cols(const FunctionCallbackInfo<Value>& args);
        static void Size(const FunctionCallbackInfo<Value>& args);

        static Persistent<Function> constructor;
        MatrixXd *value_;
};

}

#endif
