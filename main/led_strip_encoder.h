/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once



#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Type of led strip encoder configuration
     */
    typedef struct
    {
        uint32_t resolution; /*!< Encoder resolution, in Hz */
    } led_strip_encoder_config_t;

    /**
     * @brief Create RMT encoder for encoding LED strip pixels into RMT symbols
     *
     * @param[in] config Encoder configuration
     * @param[out] ret_encoder Returned encoder handle
     * @return
     *      - ESP_ERR_INVALID_ARG for any invalid arguments
     *      - ESP_ERR_NO_MEM out of memory when creating led strip encoder
     *      - ESP_OK if creating encoder successfully
     */
    esp_err_t rmt_new_led_strip_encoder(const led_strip_encoder_config_t *config, rmt_encoder_handle_t *ret_encoder);

    /**
     * @brief Simple helper function, converting HSV color space to RGB color space
     *
     * Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
     *
     */
    void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);

    void led_task();

#ifdef __cplusplus
}
#endif