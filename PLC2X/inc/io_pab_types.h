
#ifndef _IO_PAB_TYPES_H_
#define _IO_PAB_TYPES_H_

#include "gen_types.h"

/**
 * @file io_pab_types.h
 * @brief Abbildung der Hardwarepunkte auf das Speicherabbild der KBus Klemmen.
 * @author Volker Stegmann
 */



/**
 * @brief Datenstruktur zur Zusammenfassung aller analogen Eingangsgroessen
 * (Temperaturen)
 */
typedef struct ain_s {
    temp10_pt1000_t  temperatur1;     /**<   */
    temp10_pt1000_t  temperatur2;     /**<   */
    temp10_pt1000_t  temperatur3;     /**<   */
    temp10_pt1000_t  temperatur4;     /**<   */
    cnt_t            cnt1_status;     /**< Kanal 1 in 750-638 */
    cnt_t            cnt2_status;     /**< Kanal 2 in 750-638 */
} ain_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller digitalen Eingangssgroessen
 */
typedef struct din_s {
    di_bitbyte_t     digitalIn1   :1;  /**<  */
    di_bitbyte_t     digitalIn2   :1;  /**<  */
    di_bitbyte_t     digitalIn3   :1;  /**<  */
    di_bitbyte_t     digitalIn4   :1;  /**<  */
    di_bitbyte_t     reserve      :4;  /**<  */
} din_t;

/**
 * @brief Zusammenfassung der Eingaenge
 */
typedef struct Control_Input_s {
    ain_t   ain;            /**< Zuerst die analogen Eingaenge */
    din_t   din;            /**< Dann die digitalen Eingaenge  */
} Control_Input_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller analogen Ausgangsgroessen (0-10V)
 */
typedef struct aout_s {
    cnt_t           cnt1_steuer;   /**< Kanal 1 in 750-638 */
    cnt_t           cnt2_steuer;   /**< Kanal 2 in 750-638 */
} aout_t;

/**
 * @brief Datenstruktur zur Zusammenfassung aller digitalen Ausgangsgroessen
 */
typedef struct dout_s {
    do_bitbyte_t digitalOut1   :1;    /**<  */
    do_bitbyte_t digitalOut2   :1;    /**<  */
    do_bitbyte_t digitalOut3   :1;    /**<  */
    do_bitbyte_t digitalOut4   :1;    /**<  */
    di_bitbyte_t reserve       :4;    /**<  */
} dout_t;

/**
 * @brief Zusammenfassung der Ausgaenge
 */
typedef struct Control_Output_s {
    aout_t  aout;
    dout_t  dout;
} Control_Output_t;

#endif /* _IO_PAB_TYPES_H_ */

