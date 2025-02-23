/*
    Copyright 2020-2021 natinusala

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <borealis.hpp>
#include "activity/main_activity.hpp"
#include "activity/setting_activity.hpp"
#include "view/custom_button.hpp"
#include "view/auto_tab_frame.hpp"
#include "view/svg_image.hpp"

MainActivity::~MainActivity() { brls::Logger::debug("del MainActivity"); }

void MainActivity::onContentAvailable() {
    this->registerAction(
        "Settings", brls::ControllerButton::BUTTON_BACK,
        [](brls::View* view) -> bool {
            MainActivity::openSetting();
            return true;
        },
        true);

    this->registerAction(
        "Settings", brls::ControllerButton::BUTTON_START,
        [](brls::View* view) -> bool {
            MainActivity::openSetting();
            return true;
        },
        true);

    this->settingBtn->registerClickAction([](brls::View* view) -> bool {
        MainActivity::openSetting();
        return true;
    });

    this->settingBtn->getFocusEvent()->subscribe([this](bool value) {
        SVGImage* image =
            dynamic_cast<SVGImage*>(this->settingBtn->getChildren()[0]);
        if (!image) return;
        if (value) {
            image->setImageFromSVGRes("svg/ico-setting-activate.svg");
        } else {
            image->setImageFromSVGRes("svg/ico-setting.svg");
        }
    });

    this->settingBtn->setCustomNavigation(
        [this](brls::FocusDirection direction) {
            if (direction == brls::FocusDirection::RIGHT) {
                return (brls::View*)this->tabFrame->getActiveTab();
            } else if (direction == brls::FocusDirection::UP) {
                return (brls::View*)this->tabFrame->getSidebar();
            }
            return (brls::View*)nullptr;
        });
    this->settingBtn->getParent()->addGestureRecognizer(
        new brls::TapGestureRecognizer(this->settingBtn));
}

void MainActivity::openSetting() {
    brls::Application::pushActivity(new SettingActivity());
}