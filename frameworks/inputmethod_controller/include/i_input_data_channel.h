/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FM_IMMS_PROJECT_IINPUTDATACHANNEL_H
#define FM_IMMS_PROJECT_IINPUTDATACHANNEL_H
#include <errors.h>
#include "iremote_broker.h"
#include "global.h"
#include "input_method_utils.h"

/**
 * brief Definition of interface IInputDataChannel
 * It defines the remote calls from input method service to input client
 */
namespace OHOS {
namespace MiscServices {
    class IInputDataChannel : public IRemoteBroker {
    public:
        enum {
            INSERT_TEXT = 0,
            DELETE_FORWARD,
            DELETE_BACKWARD,
            CLOSE,
            GET_TEXT_BEFORE_CURSOR,
            GET_TEXT_AFTER_CURSOR,
            SEND_KEYBOARD_STATUS,
            SEND_FUNCTION_KEY,
            MOVE_CURSOR,
        };

        DECLARE_INTERFACE_DESCRIPTOR(u"ohos.miscservices.inputmethod.IInputDataChannel");

        virtual bool InsertText(const std::u16string& text) = 0;
        virtual bool DeleteForward(int32_t length) = 0;
        virtual bool DeleteBackward(int32_t length) = 0;
        virtual void Close() = 0;
        virtual std::u16string GetTextBeforeCursor() = 0;
        virtual std::u16string GetTextAfterCursor() = 0;
        virtual void SendKeyboardStatus(int32_t status) = 0;
        virtual void SendFunctionKey(int32_t funcKey) = 0;
        virtual void MoveCursor(int32_t keyCode) = 0;
    };
}
}
#endif // FM_IMMS_PROJECT_IINPUTDATACHANNEL_H
