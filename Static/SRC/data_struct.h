#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H


struct ui_vals {
    int volume = 50;
    int bass_vol = 50;
    int treb_vol = 50;

    float a4_pitch = 440.0f;

    bool default_vals();
};
#endif // !DATA_STRUCT_H