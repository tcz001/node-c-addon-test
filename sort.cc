#include <node.h>
#include <v8.h>

// #include <iostream>
// #include <stdio.h>

using namespace v8;
// using namespace std;

void Qsort(Local<Object>& a, int low, int high)
{
    if(low >= high)
    {
        return;
    }

    int first = low;
    int last = high;
    Local<Value> key = a->Get(first);
    // cout << (int) key->Uint32Value() << endl;

    while(first < last)
    {
        while(first < last && a->Get(last)->Uint32Value() >= key->Uint32Value())
        {
            --last;
        }

        a->Set(first, a->Get(last));

        while(first < last && a->Get(first)->Uint32Value() <= key->Uint32Value())
        {
            ++first;
        }

        a->Set(last, a->Get(first));
    }
    a->Set(first, key);
    Qsort(a, low, first-1);
    Qsort(a, first+1, high);
}

void doSort(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<Object> obj = args[0]->ToObject();

    int objLength = obj->Get(String::NewFromUtf8(isolate, "length"))->ToObject()->Uint32Value();

    Qsort(obj, 0, objLength - 1);

    args.GetReturnValue().Set(obj);
}



void Init(Handle<Object> target) {
  NODE_SET_METHOD(target, "sortC", doSort);
}

NODE_MODULE(addon, Init)