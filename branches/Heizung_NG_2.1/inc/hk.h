#ifndef _HK_H_
#define _HK_H_

#include "reg.h"

/* <Typen> */
/**
 * @brief Zusammenfassung der Heizkoerperheizungsparameter
 *
 * Diese Datenstruktur ist identisch mit der in fb.h definierten \ref fb_param_s.
 * Prinzipiell koennte man sie auch nur einmal in \ref gen_types.h definieren. Eventuell
 * macht es auch Sinn, auf Parameter nur ueber Pointer zu referenzieren.
 */
typedef struct hk_param_s {
    float tvl_absenk;        /**< Nachtabsenkung in Grad C         */
    float tvl_steigung;      /**< Heizkurvensteigung               */
    float tvl_niveau;        /**< Heizkurven Parallelverschiebung  */
    float tvl_min;
    float tvl_max;           /**< max. Vorlauftemperatur in Grad C */
    float at_start;
    float frostschutz;       /**< Frostschutztemperatur in Grad C  */
    float tr_sw;             /**< Raumtemperatursollwert in Grad C */
} hk_param_t;

/**
 * @brief Zusammenfassung der Eingangsgroessen der Heizkoerperheizung
 *
 * Auch diese Datenstruktur ist prinzipiell identisch mit der \ref fb_in_t.
 */
typedef struct hk_in_s {
    float        tau_mw;              /**< Aussentemperatur gemessen             */
    float        tau_avg;             /**< Aussentemperatur gemittelt            */
    float        tvl_mw;              /**< Heizungsvorlauftemperatur gemessen    */
    abgesenkt_t  zustand;             /**< Aabgesenkt oder im Normalbetrieb      */
    u8_t         partytime_flg;       /**< Partytime Flag */
} hk_in_t;

/**
 * @brief Zusammenfassung der Ausgangsgroessen der Heizkoerperheizung
 *
 * Diese Datenstruktur stellt eher die Basisklasse einer Ausgangsstruktur fuer
 * Heizungsregelkreise dar. \ref fb_out_t erbt von \ref hk_out_t.
 */
typedef struct hk_out_s {
    float            tvl_sw;        /**< Heizungsvorlauftemperatur berechneter Sollwert */
    float            mv_y;          /**< berechnete Mischventilstellung in %            */
    do_bitbyte_t     pu_sb;         /**< Pumpe Schaltzustand                            */
} hk_out_t;

/**
 * @brief Definition der Komponentenklasse der Heizkoerperheizung
 *
 * Diese Klasse ist identisch von der Definition mit \ref fb_class_s. Diese Klasse
 * koennte wieder generisch in \ref gen_types.h angelegt werden.
 */
typedef struct hk_class_s {
    reg_class_t reg;
    hk_param_t  p;
    hk_in_t     i;
    hk_out_t    o;
} hk_class_t;

/* <Typen/> */

/* <Prototypen> */
void hk_Init( hk_class_t *self );
void hk_Run( hk_class_t *self );
void hk_WriteInp(       hk_class_t  *self,
                  const float        tau_mw,
                  const float        tau_avg,
                  const float        tvl_mw,
                  const abgesenkt_t  zustand,
                  const u8_t         partytime_flg );
/* <Prototypen/> */

#endif /* _HK_H_ */

