/***************************************************************************
 *
 * Copyright 2015-2019 BES.
 * All rights reserved. All unpublished rights reserved.
 *
 * No part of this work may be used or reproduced in any form or by any
 * means, or stored in a database or retrieval system, without prior written
 * permission of BES.
 *
 * Use of this work is governed by a license granted by BES.
 * This work contains confidential and proprietary information of
 * BES. which is protected by copyright, trade secret,
 * trademark and other intellectual property rights.
 *
 ****************************************************************************/
#include "tgt_hardware.h"
#include "aud_section.h"
#include "drc.h"
#include "fir_process.h"
#include "iir_process.h"
#include "limiter.h"
#include "spectrum_fix.h"

const struct HAL_IOMUX_PIN_FUNCTION_MAP cfg_hw_pinmux_pwl[CFG_HW_PLW_NUM] = {
#if (CFG_HW_PLW_NUM > 0)
    {HAL_IOMUX_PIN_LED2, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_PULLUP_ENABLE},
    {HAL_IOMUX_PIN_LED1, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_PULLUP_ENABLE},
#endif
};

#ifdef __APP_USE_LED_INDICATE_IBRT_STATUS__
const struct HAL_IOMUX_PIN_FUNCTION_MAP cfg_ibrt_indication_pinmux_pwl[3] = {
    {HAL_IOMUX_PIN_P1_5, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_PULLUP_ENABLE},
    {HAL_IOMUX_PIN_LED1, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VBAT,
     HAL_IOMUX_PIN_PULLUP_ENABLE},
    {HAL_IOMUX_PIN_LED2, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VBAT,
     HAL_IOMUX_PIN_PULLUP_ENABLE},
};
#endif

#ifdef __KNOWLES
const struct HAL_IOMUX_PIN_FUNCTION_MAP cfg_pinmux_uart[2] = {
    {HAL_IOMUX_PIN_P2_2, HAL_IOMUX_FUNC_UART2_RX, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_NOPULL},
    {HAL_IOMUX_PIN_P2_3, HAL_IOMUX_FUNC_UART2_TX, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_NOPULL},
};
#endif

// adckey define
const uint16_t CFG_HW_ADCKEY_MAP_TABLE[CFG_HW_ADCKEY_NUMBER] = {
#if (CFG_HW_ADCKEY_NUMBER > 0)
    HAL_KEY_CODE_FN9, HAL_KEY_CODE_FN8, HAL_KEY_CODE_FN7,
    HAL_KEY_CODE_FN6, HAL_KEY_CODE_FN5, HAL_KEY_CODE_FN4,
    HAL_KEY_CODE_FN3, HAL_KEY_CODE_FN2, HAL_KEY_CODE_FN1,
#endif
};

// gpiokey define
#define CFG_HW_GPIOKEY_DOWN_LEVEL (0)
#define CFG_HW_GPIOKEY_UP_LEVEL (1)
const struct HAL_KEY_GPIOKEY_CFG_T cfg_hw_gpio_key_cfg[CFG_HW_GPIOKEY_NUM] = {
    /*
    #if (CFG_HW_GPIOKEY_NUM > 0)
    #ifdef BES_AUDIO_DEV_Main_Board_9v0
        {HAL_KEY_CODE_FN1,{HAL_IOMUX_PIN_P0_3, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        {HAL_KEY_CODE_FN2,{HAL_IOMUX_PIN_P0_0, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        {HAL_KEY_CODE_FN3,{HAL_IOMUX_PIN_P0_1, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        {HAL_KEY_CODE_FN4,{HAL_IOMUX_PIN_P0_2, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        //{HAL_KEY_CODE_FN5,{HAL_IOMUX_PIN_P2_0, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
       // {HAL_KEY_CODE_FN6,{HAL_IOMUX_PIN_P2_1, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}}, #else #ifndef
    TPORTS_KEY_COEXIST {HAL_KEY_CODE_FN1,{HAL_IOMUX_PIN_P1_3,
    HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
    HAL_IOMUX_PIN_PULLUP_ENABLE}}, {HAL_KEY_CODE_FN2,{HAL_IOMUX_PIN_P1_0,
    HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
    HAL_IOMUX_PIN_PULLUP_ENABLE}},
        // {HAL_KEY_CODE_FN3,{HAL_IOMUX_PIN_P1_2, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        {HAL_KEY_CODE_FN15,{HAL_IOMUX_PIN_P1_2, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}}, #else
        {HAL_KEY_CODE_FN1,{HAL_IOMUX_PIN_P1_3, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        {HAL_KEY_CODE_FN15,{HAL_IOMUX_PIN_P1_0, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}}, #endif #endif
    #ifdef IS_MULTI_AI_ENABLED
        //{HAL_KEY_CODE_FN13,{HAL_IOMUX_PIN_P1_3, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
        //{HAL_KEY_CODE_FN14,{HAL_IOMUX_PIN_P1_2, HAL_IOMUX_FUNC_AS_GPIO,
    HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}}, #endif #endif
    */
    // {HAL_KEY_CODE_FN1,{HAL_IOMUX_PIN_P1_5, HAL_IOMUX_FUNC_AS_GPIO,
    // HAL_IOMUX_PIN_VOLTAGE_VIO, HAL_IOMUX_PIN_PULLUP_ENABLE}},
};

// bt config
// const char *BT_LOCAL_NAME = TO_STRING(BT_DEV_NAME) "\0";
const char *BT_LOCAL_NAME = "PineBuds Pro";
const char *BLE_DEFAULT_NAME = "PineBuds Pro BLE";
uint8_t ble_addr[6] = {
#ifdef BLE_DEV_ADDR
    BLE_DEV_ADDR
#else
    0xBE, 0x99, 0x34, 0x45,
    0x56, 0x67
#endif
};
uint8_t bt_addr[6] = {
#ifdef BT_DEV_ADDR
    BT_DEV_ADDR
#else
    0x1e, 0x57, 0x34, 0x45,
    0x56, 0x67
#endif
};

/// True Wireless side configuration using resistor fitment
const struct HAL_IOMUX_PIN_FUNCTION_MAP cfg_hw_tws_channel_cfg = {
    HAL_IOMUX_PIN_P1_4, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
    HAL_IOMUX_PIN_PULLUP_ENABLE};

bool tgt_tws_get_channel_is_right(void) {
#ifdef __FIXED_TWS_EAR_SIDE__
  return TWS_EAR_SIDE_ROLE;
#else
  hal_iomux_init((struct HAL_IOMUX_PIN_FUNCTION_MAP *)&cfg_hw_tws_channel_cfg,
                 1);

  // Pinebuds pull down to 0 for right ear, but float to 1 for left ear
  return (hal_gpio_pin_get_val(
              (enum HAL_GPIO_PIN_T)cfg_hw_tws_channel_cfg.pin) == 0);
#endif
}

// audio config
// freq bands range {[0k:2.5K], [2.5k:5K], [5k:7.5K], [7.5K:10K], [10K:12.5K],
// [12.5K:15K], [15K:17.5K], [17.5K:20K]} gain range -12~+12
const int8_t cfg_aud_eq_sbc_band_settings[CFG_HW_AUD_EQ_NUM_BANDS] = {
    0, 0, 0, 0, 0, 0, 0, 0};

#define TX_PA_GAIN CODEC_TX_PA_GAIN_DEFAULT

const struct CODEC_DAC_VOL_T codec_dac_vol[TGT_VOLUME_LEVEL_QTY] = {
    {TX_PA_GAIN, 0x03, -21}, {TX_PA_GAIN, 0x03, -99},
    {TX_PA_GAIN, 0x03, -45}, {TX_PA_GAIN, 0x03, -42},
    {TX_PA_GAIN, 0x03, -39}, {TX_PA_GAIN, 0x03, -36},
    {TX_PA_GAIN, 0x03, -33}, {TX_PA_GAIN, 0x03, -30},
    {TX_PA_GAIN, 0x03, -27}, {TX_PA_GAIN, 0x03, -24},
    {TX_PA_GAIN, 0x03, -21}, {TX_PA_GAIN, 0x03, -18},
    {TX_PA_GAIN, 0x03, -15}, {TX_PA_GAIN, 0x03, -12},
    {TX_PA_GAIN, 0x03, -9},  {TX_PA_GAIN, 0x03, -6},
    {TX_PA_GAIN, 0x03, -3},  {TX_PA_GAIN, 0x03, 0}, // 0dBm
};

// MIC and channel configurations
// Pinebuds pro have the following mic's and biases
/*

 * User Voice (Talking) = MIC5 input and VMIC3 Bias
 * ANC Feed Forward     = MIC1 input and VMIC2 Bias
 * ANC Feed Backward    = MIC3 input and VMIC2 Bias
 *
 * Note that AUD_CHANNEL_MAP is offset by 1 (0 start)
*/

#define USER_TALK_MIC AUD_CHANNEL_MAP_CH4
#define USER_TALK_VMIC_CFG AUD_VMIC_MAP_VMIC3

#define CFG_HW_AUD_INPUT_PATH_MAINMIC_DEV (USER_TALK_MIC | USER_TALK_VMIC_CFG)

#ifdef VOICE_DETECTOR_EN
#define CFG_HW_AUD_INPUT_PATH_VADMIC_DEV                                       \
  (AUD_CHANNEL_MAP_CH4 | AUD_VMIC_MAP_VMIC1)
#else
#define CFG_HW_AUD_INPUT_PATH_ASRMIC_DEV                                       \
  (AUD_CHANNEL_MAP_CH4 | AUD_VMIC_MAP_VMIC3)
#endif

const struct AUD_IO_PATH_CFG_T
    cfg_audio_input_path_cfg[CFG_HW_AUD_INPUT_PATH_NUM] = {
        {
            AUD_INPUT_PATH_MAINMIC,
            CFG_HW_AUD_INPUT_PATH_MAINMIC_DEV,
        },
        {
            AUD_INPUT_PATH_LINEIN,
            CFG_HW_AUD_INPUT_PATH_MAINMIC_DEV,
        },
#ifdef VOICE_DETECTOR_EN
        {
            AUD_INPUT_PATH_VADMIC,
            CFG_HW_AUD_INPUT_PATH_MAINMIC_DEV,
        },
#else
        {
            AUD_INPUT_PATH_ASRMIC,
            CFG_HW_AUD_INPUT_PATH_MAINMIC_DEV,
        },
#endif
        {
            AUD_INPUT_PATH_ANC_FF_MIC,
            ANC_FF_MIC | ANC_VMIC_CFG,
        },
        {
            AUD_INPUT_PATH_ANC_FB_MIC,
            ANC_FB_MIC | ANC_VMIC_CFG,
        },
};

const struct HAL_IOMUX_PIN_FUNCTION_MAP app_battery_ext_charger_enable_cfg = {
    HAL_IOMUX_PIN_NUM, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
    HAL_IOMUX_PIN_PULLUP_ENABLE};

const struct HAL_IOMUX_PIN_FUNCTION_MAP app_battery_ext_charger_detecter_cfg = {
    HAL_IOMUX_PIN_P1_1, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
    HAL_IOMUX_PIN_PULLUP_ENABLE};

const struct HAL_IOMUX_PIN_FUNCTION_MAP app_battery_ext_charger_indicator_cfg =
    {HAL_IOMUX_PIN_NUM, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
     HAL_IOMUX_PIN_PULLUP_ENABLE};

/*
const struct HAL_IOMUX_PIN_FUNCTION_MAP TOUCH_INT ={
        HAL_IOMUX_PIN_P1_5, HAL_IOMUX_FUNC_AS_GPIO, HAL_IOMUX_PIN_VOLTAGE_VIO,
HAL_IOMUX_PIN_PULLUP_ENABLE
};
*/

#define IIR_COUNTER_FF_L (8)
#define IIR_COUNTER_FF_R (8)
#define IIR_COUNTER_FB_L (6)
#define IIR_COUNTER_FB_R (6)

static const struct_anc_cfg POSSIBLY_UNUSED
    AncFirCoef_50p7k_mode0 =
        {
            .anc_cfg_ff_l =
                {
                    .total_gain = 440,
                    // .total_gain = 350,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FF_L,

                    .iir_coef[0].coef_b = {42462788, -84862242, 42399478},
                    .iir_coef[0].coef_a = {134217728, -268358003, 134140286},

                    .iir_coef[1].coef_b = {135905569, -267224817, 131334465},
                    .iir_coef[1].coef_a = {134217728, -267224817, 133022306},

                    .iir_coef[2].coef_b = {132936489, -263935268, 131067941},
                    .iir_coef[2].coef_a = {134217728, -263935268, 129786702},

                    .iir_coef[3].coef_b = {131758190, -257297054, 126191415},
                    .iir_coef[3].coef_a = {134217728, -257297054, 123731878},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */
                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },
            .anc_cfg_ff_r =
                {
                    .total_gain = 382,
                    // .total_gain = 350,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FF_R,

                    .iir_coef[0].coef_b = {42462788, -84862242, 42399478},
                    .iir_coef[0].coef_a = {134217728, -268358003, 134140286},

                    .iir_coef[1].coef_b = {135905569, -267224817, 131334465},
                    .iir_coef[1].coef_a = {134217728, -267224817, 133022306},

                    .iir_coef[2].coef_b = {132936489, -263935268, 131067941},
                    .iir_coef[2].coef_a = {134217728, -263935268, 129786702},

                    .iir_coef[3].coef_b = {131758190, -257297054, 126191415},
                    .iir_coef[3].coef_a = {134217728, -257297054, 123731878},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */
                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },

            /*

            Filter1_B=[     27461831,    -54408898,     27001841];
            Filter1_A=[    134217728,   -216605724,     82606056];

            Filter2_B=[    138294078,   -267600712,    129323227];
            Filter2_A=[    134217728,   -267600712,    133399577];

            Filter3_B=[    134500015,   -268177932,    133678688];
            Filter3_A=[    134217728,   -268177932,    133960975];

            Filter4_B=[    133629164,   -264794659,    131257050];
            Filter4_A=[    134217728,   -264794659,    130668486];


            */

            .anc_cfg_fb_l =
                {
                    .total_gain = 350,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FB_L,

                    .iir_coef[0].coef_b = {27461831, -54408898, 27001841},
                    .iir_coef[0].coef_a = {134217728, -216605724, 82606056},

                    .iir_coef[1].coef_b = {138294078, -267600712, 129323227},
                    .iir_coef[1].coef_a = {134217728, -267600712, 133399577},

                    .iir_coef[2].coef_b = {134500015, -268177932, 133678688},
                    .iir_coef[2].coef_a = {134217728, -268177932, 133960975},

                    .iir_coef[3].coef_b = {133629164, -264794659, 131257050},
                    .iir_coef[3].coef_a = {134217728, -264794659, 130668486},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */

                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },
            .anc_cfg_fb_r =
                {
                    .total_gain = 350,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FB_R,

                    .iir_coef[0].coef_b = {27461831, -54408898, 27001841},
                    .iir_coef[0].coef_a = {134217728, -216605724, 82606056},

                    .iir_coef[1].coef_b = {138294078, -267600712, 129323227},
                    .iir_coef[1].coef_a = {134217728, -267600712, 133399577},

                    .iir_coef[2].coef_b = {134500015, -268177932, 133678688},
                    .iir_coef[2].coef_a = {134217728, -268177932, 133960975},

                    .iir_coef[3].coef_b = {133629164, -264794659, 131257050},
                    .iir_coef[3].coef_a = {134217728, -264794659, 130668486},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */
                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },

};

static const struct_anc_cfg POSSIBLY_UNUSED
    AncFirCoef_48k_mode0 =
        {
            .anc_cfg_ff_l =
                {
                    .total_gain = 302,
                    // .total_gain = 312,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FF_L,

                    .iir_coef[0].coef_b = {47756600, -94784525, 47030952},
                    .iir_coef[0].coef_a = {134217728, -267141655, 132927324},

                    .iir_coef[1].coef_b = {95026235, -189959646, 94933615},
                    .iir_coef[1].coef_a = {134217728, -268325174, 134107649},

                    .iir_coef[2].coef_b = {137182418, -258280236, 121193611},
                    .iir_coef[2].coef_a = {134217728, -258309065, 124129473},

                    .iir_coef[3].coef_b = {119863779, -218243094, 100875648},
                    .iir_coef[3].coef_a = {134217728, -218243094, 86521699},

                    .iir_coef[4].coef_b = {118677290, -210108781, 98119610},
                    .iir_coef[4].coef_a = {134217728, -210108781, 82579171},

                    .iir_coef[5].coef_b = {133493787, -264941439, 131633425},
                    .iir_coef[5].coef_a = {134217728, -264941439, 130909484},
                    .iir_coef[6].coef_b = {134779906, -266962984, 132210881},
                    .iir_coef[6].coef_a = {134217728, -266962984, 132773059},
                    .iir_coef[7].coef_b = {134235269, -268350403, 134115242},
                    .iir_coef[7].coef_a = {134217728, -268350430, 134132755},

                    .dac_gain_offset = 0,
                    .adc_gain_offset = -24,
                },
            .anc_cfg_ff_r =
                {
                    .total_gain = 382,
                    // .total_gain = 288,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FF_R,

                    .iir_coef[0].coef_b = {42463913, -84860822, 42396935},
                    .iir_coef[0].coef_a = {134217728, -268353516, 134135801},

                    .iir_coef[1].coef_b = {136002894, -267154076, 131168209},
                    .iir_coef[1].coef_a = {134217728, -267154076, 132953376},

                    .iir_coef[2].coef_b = {132863566, -263674901, 130888668},
                    .iir_coef[2].coef_a = {134217728, -263674901, 129534506},

                    .iir_coef[3].coef_b = {131621817, -256639526, 125746382},
                    .iir_coef[3].coef_a = {134217728, -256639526, 123150471},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},
                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */
                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },

            .anc_cfg_fb_l =
                {
                    .total_gain = 512,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FB_L,

                    .iir_coef[0].coef_b = {75662976, -150466868, 74809339},
                    .iir_coef[0].coef_a = {134217728, -267572133, 133364091},

                    .iir_coef[1].coef_b = {136259446, -267048746, 130806222},
                    .iir_coef[1].coef_a = {134217728, -267048746, 132847940},

                    .iir_coef[2].coef_b = {134365088, -267930698, 133570324},
                    .iir_coef[2].coef_a = {134217728, -267932117, 133716266},

                    .iir_coef[3].coef_b = {124587325, -241835594, 118126292},
                    .iir_coef[3].coef_a = {134217728, -241835594, 108495889},

                    .iir_coef[4].coef_b = {130235205, -255036797, 124966921},
                    .iir_coef[4].coef_a = {134217728, -255036797, 120984398},

                    .iir_coef[5].coef_b = {134327171, -268333985, 134007055},
                    .iir_coef[5].coef_a = {134217728, -268333985, 134116498},

                    .dac_gain_offset = 0,
                    .adc_gain_offset = -24,
                },
            .anc_cfg_fb_r =
                {
                    .total_gain = 511,

                    .iir_bypass_flag = 0,
                    .iir_counter = IIR_COUNTER_FB_R,

                    .iir_coef[0].coef_b = {27172676, -53803459, 26691412},
                    .iir_coef[0].coef_a = {134217728, -214195429, 80219070},

                    .iir_coef[1].coef_b = {138529480, -267551490, 129040578},
                    .iir_coef[1].coef_a = {134217728, -267551490, 133352330},

                    .iir_coef[2].coef_b = {134516353, -268162980, 133647489},
                    .iir_coef[2].coef_a = {134217728, -268162980, 133946114},

                    .iir_coef[3].coef_b = {133595549, -264581113, 131087955},
                    .iir_coef[3].coef_a = {134217728, -264581113, 130465777},

                    .iir_coef[4].coef_b = {0x8000000, 0, 0},
                    .iir_coef[4].coef_a = {0x8000000, 0, 0},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    /*		.fir_bypass_flag=1,
                            .fir_len = AUD_COEF_LEN,
                            .fir_coef =
                            {
                                32767,
                            },
                    */
                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },

#if (AUD_SECTION_STRUCT_VERSION == 2)

            /*
            1.0000000000000000,-1.5858874672928407,0.6974239598044429,0.2832267077115959,-0.3117526885614825,0.1400624733614886,
            Filter1_B=[      4751756,     -5230342,      2349858];
            Filter1_A=[     16777216,    -26606777,     11700832];


            1.0000000000000000,-1.7971697583202608,0.8159624512785459,0.9540998606028980,-1.7971697583202608,0.8618625906756480,
            Filter2_B=[     16007139,    -30151505,     14459655];
            Filter2_A=[     16777216,    -30151505,     13689578];


            1.0000000000000000,-1.9694050640918992,0.9705681145972464,0.3200483744622364,-0.6223829329788905,0.3034976090220014,
            Filter3_B=[      5369521,    -10441853,      5091845];
            Filter3_A=[     16777216,    -33041134,     16283431];


            1.0000000000000000,-1.9921619776276678,0.9921812243512138,0.9968660174712476,-1.9921712178765081,0.9953059666311256,
            Filter4_B=[     16724636,    -33423087,     16698463];
            Filter4_A=[     16777216,    -33422932,     16646039];
            */

            /*

            1.0000000000000000,-1.9868580074509832,0.9869011854430232,1.1834688902733632,-2.3614075958038656,1.1779451659756268,
            Filter1_B=[     19855313,    -39617845,     19762640];
            Filter1_A=[     16777216,    -33333946,     16557454];


            1.0000000000000000,-1.0329261527674278,0.0418392318218667,0.5812322628931170,-1.0329261527674278,0.4606069689287498,
            Filter2_B=[      9751459,    -17329625,      7727703];
            Filter2_A=[     16777216,    -17329625,       701946];


            1.0000000000000000,-1.9576081396140492,0.9591185490154677,1.0729914166044796,-1.9576081396140492,0.8861271324109881,
            Filter3_B=[     18001809,    -32843215,     14866746];
            Filter3_A=[     16777216,    -32843215,     16091339];


            1.0000000000000000,-1.9197071583239940,0.9219883336398085,0.7545642546264146,-1.4392920140632206,0.6870089347526202,
            Filter4_B=[     12659487,    -24147313,     11526097];
            Filter4_A=[     16777216,    -32207342,     15468397];


            1.0000000000000000,-1.9102108535747602,0.9139876710346515,0.9829076121866517,-1.9102108535747602,0.9310800588479999,
            Filter5_B=[     16490453,    -32048020,     15620931];
            Filter5_A=[     16777216,    -32048020,     15334169];
            */

            .anc_cfg_mc_l =
                {
                    .total_gain = 1228,

                    .iir_bypass_flag = 0,
                    .iir_counter = 5,

                    .iir_coef[0].coef_b = {19855313, -39617845, 19762640},
                    .iir_coef[0].coef_a = {16777216, -33333946, 16557454},

                    .iir_coef[1].coef_b = {9751459, -17329625, 7727703},
                    .iir_coef[1].coef_a = {16777216, -17329625, 701946},

                    .iir_coef[2].coef_b = {18001809, -32843215, 14866746},
                    .iir_coef[2].coef_a = {16777216, -32843215, 16091339},

                    .iir_coef[3].coef_b = {12659487, -24147313, 11526097},
                    .iir_coef[3].coef_a = {16777216, -32207342, 15468397},

                    .iir_coef[4].coef_b = {16490453, -32048020, 15620931},
                    .iir_coef[4].coef_a = {16777216, -32048020, 15334169},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },
            .anc_cfg_mc_r =
                {
                    .total_gain = 1331,

                    .iir_bypass_flag = 0,
                    .iir_counter = 5,

                    .iir_coef[0].coef_b = {19855313, -39617845, 19762640},
                    .iir_coef[0].coef_a = {16777216, -33333946, 16557454},

                    .iir_coef[1].coef_b = {9751459, -17329625, 7727703},
                    .iir_coef[1].coef_a = {16777216, -17329625, 701946},

                    .iir_coef[2].coef_b = {18001809, -32843215, 14866746},
                    .iir_coef[2].coef_a = {16777216, -32843215, 16091339},

                    .iir_coef[3].coef_b = {12659487, -24147313, 11526097},
                    .iir_coef[3].coef_a = {16777216, -32207342, 15468397},

                    .iir_coef[4].coef_b = {16490453, -32048020, 15620931},
                    .iir_coef[4].coef_a = {16777216, -32048020, 15334169},

                    .iir_coef[5].coef_b = {0x8000000, 0, 0},
                    .iir_coef[5].coef_a = {0x8000000, 0, 0},

                    .dac_gain_offset = 0,
                    .adc_gain_offset = (2) * 4,
                },
#endif
};


static const struct_anc_cfg POSSIBLY_UNUSED
    AncFirCoef_44p1k_mode0 = {
        .anc_cfg_ff_l =
            {
                .total_gain = 512,
                // .total_gain = 312,

                .iir_bypass_flag = 0,
                .iir_counter = IIR_COUNTER_FF_L,

                .iir_coef[0].coef_b = {47768463, -94743857, 46978979},
                .iir_coef[0].coef_a = {134217728, -267027510, 132813804},

                .iir_coef[1].coef_b = {95026887, -189952726, 94926080},
                .iir_coef[1].coef_a = {134217728, -268315406, 134097919},

                .iir_coef[2].coef_b = {137435276, -257412413, 120090247},
                .iir_coef[2].coef_a = {134217728, -257446453, 123273755},

                .iir_coef[3].coef_b = {118844778, -214442434, 98508661},
                .iir_coef[3].coef_a = {134217728, -214442434, 83135711},

                .iir_coef[4].coef_b = {117611223, -205468073, 95643298},
                .iir_coef[4].coef_a = {134217728, -205468073, 79036793},

                .iir_coef[5].coef_b = {133430657, -264618880, 131408063},
                .iir_coef[5].coef_a = {134217728, -264618880, 130620992},

                .iir_coef[6].coef_b = {134829328, -266830863, 132034457},
                .iir_coef[6].coef_a = {134217728, -266830863, 132646057},

                .iir_coef[7].coef_b = {134236821, -268342876, 134106183},
                .iir_coef[7].coef_a = {134217728, -268342908, 134125243},

                // .fir_bypass_flag = 0,
                // .fir_len = AUD_COEF_LEN,
                // .fir_coef =
                //     {
                //         0,      0,     0,      0,     0,      0,     0, 0, 0,
                //         0,     0,      0,     0,      0,     0,      0, 0, 0,
                //         0,      0,     0,      0,     0,      0, 0,      0,
                //         0,      0,     0,      0,     0,      0, 0,      0,
                //         0,      0,     0,      0,     0,      0, 0,      0,
                //         0,      0,     0,      0,     0,      0, 0,      0,
                //         0,      0,     0,      0,     0,      0, 0,      0,
                //         0,      0,     0,      0,     0,      -6144, 0, 0, 0,
                //         1,     0,      2048,  -13511, -4060, -9831,  2011, 0,
                //         2048,  -13511, -4060, -9831,  2011, 0,      0,     0,
                //         0,     0,      0,     0,      0, 0,      0,     0, 0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      -6144, 512,    0, 0,      6,     -14642,
                //         1154,  -18440, -2296, -26004, 1140, 0,      2048,
                //         22833,  -4082, -11362, 2033,  -6957,  2081, 2958,
                //         -4073, 24038,  1991,  0,      2048,  2958,   -4073,
                //         17081,  2025,  29362,  2050,  25335,  -4088, 16424,
                //         2037, 0,      2048,  23654,  -4088, -21431, 2039,
                //         28309,  1889, 16812,  -3657, 3193,   1783,  0, 2048,
                //         16812,  -3657, 31503,  1624,  9636,   1982,  -13421,
                //         -3875, 2188,   1895, 0,      2048,  -13421, -3875,
                //         11824,  1829,  -11954, 2049, -20607, -4095, -32689,
                //         2044,  0,      2048,  -20607, -4095, 20894,  2046, 0,
                //         0,     0,      0,     0,      0, 0,      0,     0, 0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0, -6144, 0,
                //         0,     0,      1, 0,      2048,  -13511, -4060,
                //         -9831,  2011,  0,      2048, -13511, -4060, -9831,
                //         2011,  0,      0,     0,      0, 0,      0,     0, 0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //         0,      0,     0,      0, 0,      0,     0,      0,
                //     },
                .reserved_for_drc =
                    {
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    },
                .dac_gain_offset = 0,
                .adc_gain_offset = -24,
            },
        .anc_cfg_ff_r =
            {
                .total_gain = 382,
                // .total_gain = 288,

                .iir_bypass_flag = 0,
                .iir_counter = IIR_COUNTER_FF_R,

                .iir_coef[0].coef_b = {42465729, -84858529, 42392831},
                .iir_coef[0].coef_a = {134217728, -268346271, 134128558},

                .iir_coef[1].coef_b = {136159949, -267039705, 130899919},
                .iir_coef[1].coef_a = {134217728, -267039705, 132842140},

                .iir_coef[2].coef_b = {132746107, -263254540, 130599907},
                .iir_coef[2].coef_a = {134217728, -263254540, 129128286},

                .iir_coef[3].coef_b = {131402980, -255575175, 125032243},
                .iir_coef[3].coef_a = {134217728, -255575175, 122217496},

                .iir_coef[4].coef_b = {0x8000000, 0, 0},
                .iir_coef[4].coef_a = {0x8000000, 0, 0},

                .iir_coef[5].coef_b = {0x8000000, 0, 0},
                .iir_coef[5].coef_a = {0x8000000, 0, 0},

                /*		.fir_bypass_flag=1,
                        .fir_len = AUD_COEF_LEN,
                        .fir_coef =
                        {
                            32767,
                        },
                */
                .dac_gain_offset = 0,
                .adc_gain_offset = (2) * 4,
            },

        /*

        Filter1_B=[     26719020,    -52852829,     26204379];
        Filter1_A=[    134217728,   -210410903,     76474119];

        Filter2_B=[    138909433,   -267471808,    128584365];
        Filter2_A=[    134217728,   -267471808,    133276071];

        Filter3_B=[    134542733,   -268138827,    133597115];
        Filter3_A=[    134217728,   -268138827,    133922120];

        Filter4_B=[    133541379,   -264235686,    130815458];
        Filter4_A=[    134217728,   -264235686,    130139109];

        */

        .anc_cfg_fb_l =
            {
                .total_gain = 512,

                .iir_bypass_flag = 0,
                .iir_counter = IIR_COUNTER_FB_L,

                .iir_coef[0].coef_b = {75679438, -150423560, 74750572},
                .iir_coef[0].coef_a = {134217728, -267495119, 133288862},

                .iir_coef[1].coef_b = {136438995, -266925170, 130506214},
                .iir_coef[1].coef_a = {134217728, -266925170, 132727481},

                .iir_coef[2].coef_b = {134378162, -267885833, 133513256},
                .iir_coef[2].coef_a = {134217728, -267887514, 133672009},

                .iir_coef[3].coef_b = {123825813, -239648340, 116853881},
                .iir_coef[3].coef_a = {134217728, -239648340, 106461967},

                .iir_coef[4].coef_b = {129901988, -253899885, 124192908},
                .iir_coef[4].coef_a = {134217728, -253899885, 119877168},

                .iir_coef[5].coef_b = {134336846, -268324991, 133988431},
                .iir_coef[5].coef_a = {134217728, -268324991, 134107550},

                /*		.fir_bypass_flag=1,
                        .fir_len = AUD_COEF_LEN,
                        .fir_coef =
                        {
                            32767,
                        },
                */
                .dac_gain_offset = 0,
                .adc_gain_offset = -24,
            },
        .anc_cfg_fb_r =
            {
                .total_gain = 511,

                .iir_bypass_flag = 0,
                .iir_counter = IIR_COUNTER_FB_R,

                .iir_coef[0].coef_b = {26719020, -52852829, 26204379},
                .iir_coef[0].coef_a = {134217728, -210410903, 76474119},

                .iir_coef[1].coef_b = {138909433, -267471808, 128584365},
                .iir_coef[1].coef_a = {134217728, -267471808, 133276071},

                .iir_coef[2].coef_b = {134542733, -268138827, 133597115},
                .iir_coef[2].coef_a = {134217728, -268138827, 133922120},

                .iir_coef[3].coef_b = {133541379, -264235686, 130815458},
                .iir_coef[3].coef_a = {134217728, -264235686, 130139109},

                .iir_coef[4].coef_b = {0x8000000, 0, 0},
                .iir_coef[4].coef_a = {0x8000000, 0, 0},

                .iir_coef[5].coef_b = {0x8000000, 0, 0},
                .iir_coef[5].coef_a = {0x8000000, 0, 0},

                /*		.fir_bypass_flag=1,
                        .fir_len = AUD_COEF_LEN,
                        .fir_coef =
                        {
                            32767,
                        },
                */
                .dac_gain_offset = 0,
                .adc_gain_offset = (2) * 4,
            },
#if (AUD_SECTION_STRUCT_VERSION == 2)

        /*

        Filter1_B=[     19847881,    -39594823,     19747071];
        Filter1_A=[     16777216,    -33314517,     16538159];

        Filter2_B=[      9442890,    -16603187,      7330251];
        Filter2_A=[     16777216,    -16603187,        -4075];

        Filter3_B=[     18107639,    -32779315,     14701642];
        Filter3_A=[     16777216,    -32779315,     16032065];

        Filter4_B=[     12666347,    -24058210,     11437046];
        Filter4_A=[     16777216,    -32089673,     15357640];

        Filter5_B=[     16466312,    -31915122,     15523589];
        Filter5_A=[     16777216,    -31915122,     15212684];
        */

        .anc_cfg_mc_l =
            {
                .total_gain = 1228,

                .iir_bypass_flag = 0,
                .iir_counter = 5,

                .iir_coef[0].coef_b = {19847881, -39594823, 19747071},
                .iir_coef[0].coef_a = {16777216, -33314517, 16538159},

                .iir_coef[1].coef_b = {9442890, -16603187, 7330251},
                .iir_coef[1].coef_a = {16777216, -16603187, -4075},

                .iir_coef[2].coef_b = {18107639, -32779315, 14701642},
                .iir_coef[2].coef_a = {16777216, -32779315, 16032065},

                .iir_coef[3].coef_b = {12666347, -24058210, 11437046},
                .iir_coef[3].coef_a = {16777216, -32089673, 15357640},

                .iir_coef[4].coef_b = {16466312, -31915122, 15523589},
                .iir_coef[4].coef_a = {16777216, -31915122, 15212684},

                .iir_coef[5].coef_b = {0x8000000, 0, 0},
                .iir_coef[5].coef_a = {0x8000000, 0, 0},

                .dac_gain_offset = 0,
                .adc_gain_offset = (2) * 4,
            },
        .anc_cfg_mc_r =
            {
                .total_gain = 1331,

                .iir_bypass_flag = 0,
                .iir_counter = 5,

                .iir_coef[0].coef_b = {19847881, -39594823, 19747071},
                .iir_coef[0].coef_a = {16777216, -33314517, 16538159},

                .iir_coef[1].coef_b = {9442890, -16603187, 7330251},
                .iir_coef[1].coef_a = {16777216, -16603187, -4075},

                .iir_coef[2].coef_b = {18107639, -32779315, 14701642},
                .iir_coef[2].coef_a = {16777216, -32779315, 16032065},

                .iir_coef[3].coef_b = {12666347, -24058210, 11437046},
                .iir_coef[3].coef_a = {16777216, -32089673, 15357640},

                .iir_coef[4].coef_b = {16466312, -31915122, 15523589},
                .iir_coef[4].coef_a = {16777216, -31915122, 15212684},

                .iir_coef[5].coef_b = {0x8000000, 0, 0},
                .iir_coef[5].coef_a = {0x8000000, 0, 0},

                .dac_gain_offset = 0,
                .adc_gain_offset = (2) * 4,
            },
#endif

};

const struct_anc_cfg *anc_coef_list_50p7k[ANC_COEF_LIST_NUM] = {
    &AncFirCoef_50p7k_mode0,
#if (ANC_COEF_LIST_NUM == 2)
    &AncFirCoef_50p7k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 3)
    &AncFirCoef_50p7k_mode0, &AncFirCoef_50p7k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 4)
    &AncFirCoef_50p7k_mode0, &AncFirCoef_50p7k_mode0, &AncFirCoef_50p7k_mode0,
#endif
};

const struct_anc_cfg *anc_coef_list_48k[ANC_COEF_LIST_NUM] = {
    &AncFirCoef_48k_mode0,
#if (ANC_COEF_LIST_NUM == 2)
    &AncFirCoef_48k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 3)
    &AncFirCoef_48k_mode0, &AncFirCoef_48k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 4)
    &AncFirCoef_48k_mode0, &AncFirCoef_48k_mode0, &AncFirCoef_48k_mode0,
#endif
};

const struct_anc_cfg *anc_coef_list_44p1k[ANC_COEF_LIST_NUM] = {
    &AncFirCoef_44p1k_mode0,
#if (ANC_COEF_LIST_NUM == 2)
    &AncFirCoef_44p1k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 3)
    &AncFirCoef_44p1k_mode0, &AncFirCoef_44p1k_mode0,
#endif
#if (ANC_COEF_LIST_NUM == 4)
    &AncFirCoef_44p1k_mode0, &AncFirCoef_44p1k_mode0, &AncFirCoef_44p1k_mode0,
#endif
};

const IIR_CFG_T audio_eq_sw_iir_cfg = {.gain0 = 0,
                                       .gain1 = 0,
                                       .num = 14,
                                       .param = {
                                           {IIR_TYPE_PEAK, -2.18, 10, 2},
                                           {IIR_TYPE_PEAK, 7.27, 21, 2},
                                           {IIR_TYPE_PEAK, 2.13, 42, 2},
                                           {IIR_TYPE_PEAK, -1.53, 83, 2},
                                           {IIR_TYPE_PEAK, -0.9, 120, 2},
                                           {IIR_TYPE_PEAK, -4.23, 166, 2},
                                           {IIR_TYPE_PEAK, -1.08, 333, 2},
                                           {IIR_TYPE_PEAK, -1.37, 577, 2},
                                           {IIR_TYPE_PEAK, 0.8, 1000, 2},
                                           {IIR_TYPE_PEAK, 5.35, 2000, 2},
                                           {IIR_TYPE_PEAK, 3.2, 4000, 2},
                                           {IIR_TYPE_PEAK, -4.96, 8000, 2},
                                           {IIR_TYPE_PEAK, 13.58, 16000, 2},
                                           {IIR_TYPE_PEAK, 8.89, 20000, 2},
                                       }};

const IIR_CFG_T *const audio_eq_sw_iir_cfg_list[EQ_SW_IIR_LIST_NUM] = {
    &audio_eq_sw_iir_cfg,
};

const FIR_CFG_T audio_eq_hw_fir_cfg_44p1k = {.gain = 0.0f,
                                             .len = 384,
                                             .coef = {
                                                 (1 << 23) - 1,
                                             }};

const FIR_CFG_T audio_eq_hw_fir_cfg_48k = {.gain = 0.0f,
                                           .len = 384,
                                           .coef = {
                                               (1 << 23) - 1,
                                           }};

const FIR_CFG_T audio_eq_hw_fir_cfg_96k = {.gain = 0.0f,
                                           .len = 384,
                                           .coef = {
                                               (1 << 23) - 1,
                                           }};

const FIR_CFG_T *const audio_eq_hw_fir_cfg_list[EQ_HW_FIR_LIST_NUM] = {
    &audio_eq_hw_fir_cfg_44p1k,
    &audio_eq_hw_fir_cfg_48k,
    &audio_eq_hw_fir_cfg_96k,
};

// hardware dac iir eq
const IIR_CFG_T audio_eq_hw_dac_iir_cfg = audio_eq_sw_iir_cfg;

const IIR_CFG_T *const POSSIBLY_UNUSED
    audio_eq_hw_dac_iir_cfg_list[EQ_HW_DAC_IIR_LIST_NUM] = {
        &audio_eq_hw_dac_iir_cfg,
};

// hardware dac iir eq
const IIR_CFG_T audio_eq_hw_adc_iir_adc_cfg = audio_eq_sw_iir_cfg;

const IIR_CFG_T *const POSSIBLY_UNUSED
    audio_eq_hw_adc_iir_cfg_list[EQ_HW_ADC_IIR_LIST_NUM] = {
        &audio_eq_hw_adc_iir_adc_cfg,
};

// hardware iir eq
const IIR_CFG_T audio_eq_hw_iir_cfg = audio_eq_sw_iir_cfg;

const IIR_CFG_T *const POSSIBLY_UNUSED
    audio_eq_hw_iir_cfg_list[EQ_HW_IIR_LIST_NUM] = {
        &audio_eq_hw_iir_cfg,
};

const DrcConfig audio_drc_cfg = {.knee = 3,
                                 .filter_type = {14, -1},
                                 .band_num = 2,
                                 .look_ahead_time = 10,
                                 .band_settings = {
                                     {-20, 0, 2, 3, 3000, 1},
                                     {-20, 0, 2, 3, 3000, 1},
                                 }};

const LimiterConfig audio_drc2_cfg = {
    .knee = 2,
    .look_ahead_time = 10,
    .threshold = -20,
    .makeup_gain = 19,
    .ratio = 1000,
    .attack_time = 3,
    .release_time = 3000,
};

const SpectrumFixConfig audio_spectrum_cfg = {
    .freq_num = 9,
    .freq_list = {200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800},
};
