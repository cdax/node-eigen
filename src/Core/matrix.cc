#include "matrix.h"

namespace eigen {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Integer;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Exception;

using Eigen::MatrixXd;
using Eigen::Dynamic;

Persistent<Function> Matrix::constructor;

Matrix::Matrix() {
    value_ = new MatrixXd();
}

Matrix::Matrix(uint32_t rows) {
    value_ = new MatrixXd(rows, 1);
}

Matrix::Matrix(uint32_t rows, uint32_t cols) {
    value_ = new MatrixXd(rows, cols);
}

Matrix::~Matrix() {
    delete value_;
}

void Matrix::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Matrix"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "rows", Rows);
    NODE_SET_PROTOTYPE_METHOD(tpl, "cols", Cols);
    NODE_SET_PROTOTYPE_METHOD(tpl, "size", Size);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "Matrix"),
                    tpl->GetFunction());
}

void Matrix::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        // Invoked as a constructor
        Matrix *matrix;
        switch (args.Length()) {

            case 0:
                // Null matrix
                matrix = new Matrix();
                break;

            case 1:
                // Row-vector of doubles
                if (!args[0]->IsUint32()) {
                    isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Incorrect arguments")));
                    return;
                }
                matrix = new Matrix(args[0]->Uint32Value());
                break;

            case 2:
                // Matrix of doubles
                if (!args[0]->IsUint32() || !args[1]->IsUint32()) {
                    isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Incorrect arguments")));
                    return;
                }
                matrix = new Matrix(args[0]->Uint32Value(), args[1]->Uint32Value());
                break;

            default:
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Incorrect number of arguments")));
                return;
        }
        matrix->Wrap(args.This());
        args.GetReturnValue().Set(args.This());

    } else {
        // Invoked as plain function; turn into constructor
        int argc = args.Length();
        Local<Value> argv[2];
        switch (argc) {

            case 0:
                break;

            case 1:
                argv[0] = args[0];
                break;

            case 2:
                argv[0] = args[0];
                argv[1] = args[1];
                break;

            default:
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Incorrect number of arguments")));
                return;

        }
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void Matrix::Rows(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Matrix* matrix = ObjectWrap::Unwrap<Matrix>(args.Holder());
    args.GetReturnValue().Set(Integer::New(isolate, matrix->value_->rows()));
}

void Matrix::Cols(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Matrix* matrix = ObjectWrap::Unwrap<Matrix>(args.Holder());
    args.GetReturnValue().Set(Integer::New(isolate, matrix->value_->cols()));
}

void Matrix::Size(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Matrix* matrix = ObjectWrap::Unwrap<Matrix>(args.Holder());
    args.GetReturnValue().Set(Integer::New(isolate, matrix->value_->size()));
}

}
