/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "Style.h"

#include <Corrade/Utility/Resource.h>
#include <Magnum/Buffer.h>
#include <Magnum/Shader.h>
#include <Magnum/Texture.h>
#include <Magnum/Version.h>

#include "Magnum/Ui/Widget.h"

#ifdef MAGNUM_BUILD_STATIC
static void importShaderResources() {
    CORRADE_RESOURCE_INITIALIZE(MagnumUi_RESOURCES)
}
#endif

namespace Magnum { namespace Ui {

namespace Implementation {

UnsignedByte backgroundColorIndex(const Type type, const Style style, const State state) {
    enum: UnsignedByte {
        Hidden = 0,

        ModalDefaultDefault,
        ModalDefaultDisabled,
        ModalPrimaryDefault,
        ModalPrimaryDisabled,
        ModalSuccessDefault,
        ModalSuccessDisabled,
        ModalInfoDefault,
        ModalInfoDisabled,
        ModalWarningDefault,
        ModalWarningDisabled,
        ModalDangerDefault,
        ModalDangerDisabled,
        ModalDimDefault,

        BackgroundColorCount
    };

    static_assert(UnsignedByte(BackgroundColorCount) <= UnsignedByte(Implementation::BackgroundColorCount), "");

    if(state == State::Hidden)
        return Hidden;

    const UnsignedInt encoded = (UnsignedInt(type) << 16) |
                                (UnsignedInt(style) << 8) |
                                 UnsignedInt(state);

    switch(encoded) {
        #define _c(type, style, state)                                      \
            case (UnsignedInt(Type::type) << 16) |                          \
                 (UnsignedInt(Style::style) << 8) |                         \
                  UnsignedInt(State::state):                                \
                return type ## style ## state;
        _c(Modal, Default, Default)
        _c(Modal, Default, Disabled)
        _c(Modal, Primary, Default)
        _c(Modal, Primary, Disabled)
        _c(Modal, Success, Default)
        _c(Modal, Success, Disabled)
        _c(Modal, Info, Default)
        _c(Modal, Info, Disabled)
        _c(Modal, Warning, Default)
        _c(Modal, Warning, Disabled)
        _c(Modal, Danger, Default)
        _c(Modal, Danger, Disabled)
        _c(Modal, Dim, Default)
        #undef _c
    }

    CORRADE_ASSERT(false, "Ui::StyleConfiguration: unsupported background color index" << type << style << state, 0);
    CORRADE_ASSERT_UNREACHABLE();
}

UnsignedByte foregroundColorIndex(const Type type, const Style style, const State state) {
    enum: UnsignedByte {
        Hidden = 0,

        ButtonDefaultDefault,
        ButtonDefaultHover,
        ButtonDefaultPressed,
        ButtonDefaultDisabled,
        ButtonPrimaryDefault,
        ButtonPrimaryHover,
        ButtonPrimaryPressed,
        ButtonPrimaryDisabled,
        ButtonSuccessDefault,
        ButtonSuccessHover,
        ButtonSuccessPressed,
        ButtonSuccessDisabled,
        ButtonInfoDefault,
        ButtonInfoHover,
        ButtonInfoPressed,
        ButtonInfoDisabled,
        ButtonWarningDefault,
        ButtonWarningHover,
        ButtonWarningPressed,
        ButtonWarningDisabled,
        ButtonDangerDefault,
        ButtonDangerHover,
        ButtonDangerPressed,
        ButtonDangerDisabled,
        ButtonDimDefault,
        ButtonDimHover,
        ButtonDimPressed,
        ButtonDimDisabled,

        InputDefaultDefault,
        InputDefaultHover,
        InputDefaultPressed,
        InputDefaultActive,
        InputDefaultDisabled,
        InputPrimaryDefault,
        InputPrimaryHover,
        InputPrimaryPressed,
        InputPrimaryActive,
        InputPrimaryDisabled,
        InputSuccessDefault,
        InputSuccessHover,
        InputSuccessPressed,
        InputSuccessActive,
        InputSuccessDisabled,
        InputInfoDefault,
        InputInfoHover,
        InputInfoPressed,
        InputInfoActive,
        InputInfoDisabled,
        InputWarningDefault,
        InputWarningHover,
        InputWarningPressed,
        InputWarningActive,
        InputWarningDisabled,
        InputDangerDefault,
        InputDangerHover,
        InputDangerPressed,
        InputDangerActive,
        InputDangerDisabled,
        InputDimDefault,
        InputDimHover,
        InputDimPressed,
        InputDimActive,
        InputDimDisabled,

        ForegroundColorCount
    };

    static_assert(UnsignedByte(ForegroundColorCount) <= UnsignedByte(Implementation::ForegroundColorCount), "");

    if(state == State::Hidden)
        return Hidden;

    const UnsignedInt encoded = (UnsignedInt(type) << 16) |
                                (UnsignedInt(style) << 8) |
                                 UnsignedInt(state);

    switch(encoded) {
        #define _c(type, style, state)                                      \
            case (UnsignedInt(Type::type) << 16) |                          \
                 (UnsignedInt(Style::style) << 8) |                         \
                  UnsignedInt(State::state):                                \
                return type ## style ## state;
        _c(Button, Default, Default)
        _c(Button, Default, Hover)
        _c(Button, Default, Pressed)
        _c(Button, Default, Disabled)
        _c(Button, Primary, Default)
        _c(Button, Primary, Hover)
        _c(Button, Primary, Pressed)
        _c(Button, Primary, Disabled)
        _c(Button, Success, Default)
        _c(Button, Success, Hover)
        _c(Button, Success, Pressed)
        _c(Button, Success, Disabled)
        _c(Button, Info, Default)
        _c(Button, Info, Hover)
        _c(Button, Info, Pressed)
        _c(Button, Info, Disabled)
        _c(Button, Warning, Default)
        _c(Button, Warning, Hover)
        _c(Button, Warning, Pressed)
        _c(Button, Warning, Disabled)
        _c(Button, Danger, Default)
        _c(Button, Danger, Hover)
        _c(Button, Danger, Pressed)
        _c(Button, Danger, Disabled)
        _c(Button, Dim, Default)
        _c(Button, Dim, Hover)
        _c(Button, Dim, Pressed)
        _c(Button, Dim, Disabled)

        _c(Input, Default, Default)
        _c(Input, Default, Hover)
        _c(Input, Default, Pressed)
        _c(Input, Default, Active)
        _c(Input, Default, Disabled)
        _c(Input, Primary, Default)
        _c(Input, Primary, Hover)
        _c(Input, Primary, Pressed)
        _c(Input, Primary, Active)
        _c(Input, Primary, Disabled)
        _c(Input, Success, Default)
        _c(Input, Success, Hover)
        _c(Input, Success, Pressed)
        _c(Input, Success, Active)
        _c(Input, Success, Disabled)
        _c(Input, Info, Default)
        _c(Input, Info, Hover)
        _c(Input, Info, Pressed)
        _c(Input, Info, Active)
        _c(Input, Info, Disabled)
        _c(Input, Warning, Default)
        _c(Input, Warning, Hover)
        _c(Input, Warning, Pressed)
        _c(Input, Warning, Active)
        _c(Input, Warning, Disabled)
        _c(Input, Danger, Default)
        _c(Input, Danger, Hover)
        _c(Input, Danger, Pressed)
        _c(Input, Danger, Active)
        _c(Input, Danger, Disabled)
        _c(Input, Dim, Default)
        _c(Input, Dim, Hover)
        _c(Input, Dim, Pressed)
        _c(Input, Dim, Active)
        _c(Input, Dim, Disabled)
        #undef _c
    }

    CORRADE_ASSERT(false, "Ui::StyleConfiguration: unsupported foreground color index" << type << style << state, 0);
    CORRADE_ASSERT_UNREACHABLE();
}

UnsignedByte textColorIndex(const Type type, const Style style, const State state) {
    enum: UnsignedByte {
        Hidden = 0,

        ButtonDefaultDefault,
        ButtonDefaultHover,
        ButtonDefaultPressed,
        ButtonDefaultDisabled,
        ButtonPrimaryDefault,
        ButtonPrimaryHover,
        ButtonPrimaryPressed,
        ButtonPrimaryDisabled,
        ButtonSuccessDefault,
        ButtonSuccessHover,
        ButtonSuccessPressed,
        ButtonSuccessDisabled,
        ButtonInfoDefault,
        ButtonInfoHover,
        ButtonInfoPressed,
        ButtonInfoDisabled,
        ButtonWarningDefault,
        ButtonWarningHover,
        ButtonWarningPressed,
        ButtonWarningDisabled,
        ButtonDangerDefault,
        ButtonDangerHover,
        ButtonDangerPressed,
        ButtonDangerDisabled,
        ButtonDimDefault,
        ButtonDimHover,
        ButtonDimPressed,
        ButtonDimDisabled,
        ButtonFlatDefault,
        ButtonFlatHover,
        ButtonFlatPressed,
        ButtonFlatDisabled,

        LabelDefaultDefault,
        LabelDefaultDisabled,
        LabelPrimaryDefault,
        LabelPrimaryDisabled,
        LabelSuccessDefault,
        LabelSuccessDisabled,
        LabelInfoDefault,
        LabelInfoDisabled,
        LabelWarningDefault,
        LabelWarningDisabled,
        LabelDangerDefault,
        LabelDangerDisabled,
        LabelDimDefault,
        LabelDimDisabled,

        InputDefaultDefault,
        InputDefaultHover,
        InputDefaultPressed,
        InputDefaultActive,
        InputDefaultDisabled,
        InputPrimaryDefault,
        InputPrimaryHover,
        InputPrimaryPressed,
        InputPrimaryActive,
        InputPrimaryDisabled,
        InputSuccessDefault,
        InputSuccessHover,
        InputSuccessPressed,
        InputSuccessActive,
        InputSuccessDisabled,
        InputInfoDefault,
        InputInfoHover,
        InputInfoPressed,
        InputInfoActive,
        InputInfoDisabled,
        InputWarningDefault,
        InputWarningHover,
        InputWarningPressed,
        InputWarningActive,
        InputWarningDisabled,
        InputDangerDefault,
        InputDangerHover,
        InputDangerPressed,
        InputDangerActive,
        InputDangerDisabled,
        InputDimDefault,
        InputDimHover,
        InputDimPressed,
        InputDimActive,
        InputDimDisabled,
        InputFlatDefault,
        InputFlatHover,
        InputFlatPressed,
        InputFlatActive,
        InputFlatDisabled,

        TextColorCount
    };

    static_assert(UnsignedByte(TextColorCount) <= UnsignedByte(Implementation::TextColorCount), "");

    if(state == State::Hidden)
        return Hidden;

    const UnsignedInt encoded = (UnsignedInt(type) << 16) |
                                (UnsignedInt(style) << 8) |
                                 UnsignedInt(state);

    switch(encoded) {
        #define _c(type, style, state)                                      \
            case (UnsignedInt(Type::type) << 16) |                          \
                 (UnsignedInt(Style::style) << 8) |                         \
                  UnsignedInt(State::state):                                \
                return type ## style ## state;
        _c(Button, Default, Default)
        _c(Button, Default, Hover)
        _c(Button, Default, Pressed)
        _c(Button, Default, Disabled)
        _c(Button, Primary, Default)
        _c(Button, Primary, Hover)
        _c(Button, Primary, Pressed)
        _c(Button, Primary, Disabled)
        _c(Button, Success, Default)
        _c(Button, Success, Hover)
        _c(Button, Success, Pressed)
        _c(Button, Success, Disabled)
        _c(Button, Info, Default)
        _c(Button, Info, Hover)
        _c(Button, Info, Pressed)
        _c(Button, Info, Disabled)
        _c(Button, Warning, Default)
        _c(Button, Warning, Hover)
        _c(Button, Warning, Pressed)
        _c(Button, Warning, Disabled)
        _c(Button, Danger, Default)
        _c(Button, Danger, Hover)
        _c(Button, Danger, Pressed)
        _c(Button, Danger, Disabled)
        _c(Button, Dim, Default)
        _c(Button, Dim, Hover)
        _c(Button, Dim, Pressed)
        _c(Button, Dim, Disabled)
        _c(Button, Flat, Default)
        _c(Button, Flat, Hover)
        _c(Button, Flat, Pressed)
        _c(Button, Flat, Disabled)

        _c(Label, Default, Default)
        _c(Label, Default, Disabled)
        _c(Label, Primary, Default)
        _c(Label, Primary, Disabled)
        _c(Label, Success, Default)
        _c(Label, Success, Disabled)
        _c(Label, Info, Default)
        _c(Label, Info, Disabled)
        _c(Label, Warning, Default)
        _c(Label, Warning, Disabled)
        _c(Label, Danger, Default)
        _c(Label, Danger, Disabled)
        _c(Label, Dim, Default)
        _c(Label, Dim, Disabled)

        _c(Input, Default, Default)
        _c(Input, Default, Hover)
        _c(Input, Default, Pressed)
        _c(Input, Default, Active)
        _c(Input, Default, Disabled)
        _c(Input, Primary, Default)
        _c(Input, Primary, Hover)
        _c(Input, Primary, Pressed)
        _c(Input, Primary, Active)
        _c(Input, Primary, Disabled)
        _c(Input, Success, Default)
        _c(Input, Success, Hover)
        _c(Input, Success, Pressed)
        _c(Input, Success, Active)
        _c(Input, Success, Disabled)
        _c(Input, Info, Default)
        _c(Input, Info, Hover)
        _c(Input, Info, Pressed)
        _c(Input, Info, Active)
        _c(Input, Info, Disabled)
        _c(Input, Warning, Default)
        _c(Input, Warning, Hover)
        _c(Input, Warning, Pressed)
        _c(Input, Warning, Active)
        _c(Input, Warning, Disabled)
        _c(Input, Danger, Default)
        _c(Input, Danger, Hover)
        _c(Input, Danger, Pressed)
        _c(Input, Danger, Active)
        _c(Input, Danger, Disabled)
        _c(Input, Dim, Default)
        _c(Input, Dim, Hover)
        _c(Input, Dim, Pressed)
        _c(Input, Dim, Active)
        _c(Input, Dim, Disabled)
        _c(Input, Flat, Default)
        _c(Input, Flat, Hover)
        _c(Input, Flat, Pressed)
        _c(Input, Flat, Active)
        _c(Input, Flat, Disabled)
        #undef _c
    }

    CORRADE_ASSERT(false, "Ui::StyleConfiguration: unsupported text color index" << type << style << state, 0);
    CORRADE_ASSERT_UNREACHABLE();
}

namespace {

State stateForFlags(StateFlags flags) {
    if(flags & StateFlag::Hidden) return State::Hidden;
    if(flags & StateFlag::Disabled) return State::Disabled;
    if(flags & StateFlag::Pressed) return State::Pressed;
    if(flags & StateFlag::Active) return State::Active;
    if(flags & StateFlag::Hovered) return State::Hover;
    return State::Default;
}

}

UnsignedByte backgroundColorIndex(const Type type, const Style style, const StateFlags flags) {
    return backgroundColorIndex(type, style, stateForFlags(flags));
}

UnsignedByte foregroundColorIndex(const Type type, const Style style, const StateFlags flags) {
    return foregroundColorIndex(type, style, stateForFlags(flags));
}

UnsignedByte textColorIndex(const Type type, const Style style, const StateFlags flags) {
    return textColorIndex(type, style, stateForFlags(flags));
}

}

Debug& operator<<(Debug& debug, const Type value) {
    switch(value) {
        #define _c(value) case Type::value: return debug << "Type::" #value;
        _c(Button)
        _c(Input)
        _c(Label)
        _c(Modal)
        #undef _c
    }

    return debug << "Type::(invalid)";
}

Debug& operator<<(Debug& debug, const State value) {
    switch(value) {
        #define _c(value) case State::value: return debug << "State::" #value;
        _c(Default)
        _c(Hover)
        _c(Pressed)
        _c(Active)
        _c(Disabled)
        _c(Hidden)
        #undef _c
    }

    return debug << "State::(invalid)";
}

Debug& operator<<(Debug& debug, const Style value) {
    switch(value) {
        #define _c(value) case Style::value: return debug << "Style::" #value;
        _c(Default)
        _c(Primary)
        _c(Success)
        _c(Info)
        _c(Warning)
        _c(Danger)
        _c(Dim)
        _c(Flat)
        #undef _c
    }

    return debug << "Style::(invalid)";
}

StyleConfiguration::StyleConfiguration() = default;

StyleConfiguration defaultStyleConfiguration() {
    /** @todo */
    return StyleConfiguration{};
}

void StyleConfiguration::pack(Buffer& backgroundUniforms, Buffer& foregroundUniforms, Buffer& textUniforms) const {
    backgroundUniforms.setData({&_background, 1}, BufferUsage::StaticDraw);
    foregroundUniforms.setData({&_foreground, 1}, BufferUsage::StaticDraw);
    textUniforms.setData({&_text, 1}, BufferUsage::StaticDraw);
}

namespace Implementation {

AbstractQuadShader& AbstractQuadShader::bindCornerTexture(Texture2D& texture) {
    texture.bind(0);
    return *this;
}

BackgroundShader::BackgroundShader() {
    #ifdef MAGNUM_BUILD_STATIC
    if(!Utility::Resource::hasGroup("MagnumUi"))
        importShaderResources();
    #endif

    Utility::Resource rs{"MagnumUi"};

    Shader vert{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Vertex};
    Shader frag{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Fragment};
    vert.addSource("#define BACKGROUND_COLOR_COUNT " + std::to_string(Implementation::BackgroundColorCount) + "\n")
        .addSource(rs.get("BackgroundShader.vert"));
    frag.addSource("#define BACKGROUND_COLOR_COUNT " + std::to_string(Implementation::BackgroundColorCount) + "\n")
        .addSource(rs.get("BackgroundShader.frag"));

    CORRADE_INTERNAL_ASSERT(Shader::compile({vert, frag}));
    attachShaders({vert, frag});

    CORRADE_INTERNAL_ASSERT(link());

    setUniform(uniformLocation("cornerTextureData"), 0);
    setUniformBlockBinding(uniformBlockIndex("Style"), 0);
    _transformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");
}

BackgroundShader& BackgroundShader::bindStyleBuffer(Buffer& buffer) {
    buffer.bind(Buffer::Target::Uniform, 0);
    return *this;
}

ForegroundShader::ForegroundShader() {
    #ifdef MAGNUM_BUILD_STATIC
    if(!Utility::Resource::hasGroup("MagnumUi"))
        importShaderResources();
    #endif

    Utility::Resource rs{"MagnumUi"};

    Shader vert{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Vertex};
    Shader frag{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Fragment};
    vert.addSource("#define FOREGROUND_COLOR_COUNT " + std::to_string(Implementation::ForegroundColorCount) + "\n")
        .addSource(rs.get("ForegroundShader.vert"));
    frag.addSource("#define FOREGROUND_COLOR_COUNT " + std::to_string(Implementation::ForegroundColorCount) + "\n")
        .addSource(rs.get("ForegroundShader.frag"));

    CORRADE_INTERNAL_ASSERT(Shader::compile({vert, frag}));
    attachShaders({vert, frag});

    CORRADE_INTERNAL_ASSERT(link());

    setUniform(uniformLocation("cornerTextureData"), 0);
    setUniformBlockBinding(uniformBlockIndex("Style"), 1);
    _transformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");
}

ForegroundShader& ForegroundShader::bindStyleBuffer(Buffer& buffer) {
    buffer.bind(Buffer::Target::Uniform, 1);
    return *this;
}

TextShader::TextShader() {
    #ifdef MAGNUM_BUILD_STATIC
    if(!Utility::Resource::hasGroup("MagnumUi"))
        importShaderResources();
    #endif

    Utility::Resource rs{"MagnumUi"};

    Shader vert{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Vertex};
    Shader frag{
        #ifndef MAGNUM_TARGET_GLES
        Version::GL330,
        #else
        Version::GLES300,
        #endif
        Shader::Type::Fragment};
    vert.addSource(rs.get("TextShader.vert"));
    frag.addSource("#define TEXT_COLOR_COUNT " + std::to_string(Implementation::TextColorCount) + "\n")
        .addSource(rs.get("TextShader.frag"));

    CORRADE_INTERNAL_ASSERT(Shader::compile({vert, frag}));
    attachShaders({vert, frag});

    CORRADE_INTERNAL_ASSERT(link());

    setUniformBlockBinding(uniformBlockIndex("Style"), 2);
    _transformationProjectionMatrixUniform = uniformLocation("transformationProjectionMatrix");
    setUniform(uniformLocation("textureData"), 1);
}

TextShader& TextShader::bindGlyphCacheTexture(Texture2D& texture) {
    texture.bind(1);
    return *this;
}

TextShader& TextShader::bindStyleBuffer(Buffer& buffer) {
    buffer.bind(Buffer::Target::Uniform, 2);
    return *this;
}

}}}