#include "../dependencies/kxmx_bluemchen/kxmx_bluemchen.h"
#include <string>

using namespace kxmx;
using namespace daisy;

Bluemchen bluemchen;
Parameter knob1;
Parameter knob2;
Parameter cv1;
Parameter cv2;

void UpdateOled() {
    bluemchen.display.Fill(false);

    // Display Encoder test increment value and pressed state
    bluemchen.display.SetCursor(0, 0);
    std::string str = "Hello Eurorack!";
    char *cstr = &str[0];
    bluemchen.display.WriteString(cstr, Font_6x8, true);

    bluemchen.display.Update();
}

void UpdateControls() {
    bluemchen.ProcessAllControls();
}

void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t size) {
    UpdateControls();

    for (size_t i = 0; i < size; i++) {

        float sig_l = in[0][i];
        float sig_r = in[1][i];

        out[0][i] = sig_l;
        out[1][i] = sig_r;
    }
}

int main(void) {
    bluemchen.Init();
    bluemchen.StartAdc();

    knob1.Init(bluemchen.knobs[bluemchen.KNOB_1], 0.001f, 0.1f, Parameter::LINEAR);
    knob2.Init(bluemchen.knobs[bluemchen.KNOB_2], 0.001f, 0.5f, Parameter::LINEAR);

    cv1.Init(bluemchen.cv[bluemchen.CV_1], -5000.0f, 5000.0f, Parameter::LINEAR);
    cv2.Init(bluemchen.cv[bluemchen.CV_2], -5000.0f, 5000.0f, Parameter::LINEAR);

    bluemchen.StartAudio(AudioCallback);

    while (1) {
        UpdateControls();
        UpdateOled();
    }
}
