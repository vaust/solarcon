/*
 * anlage_types.h
 *
 *  Created on: 22.03.2011
 *      Author: stegmv
 */

#ifndef _ALL_TYPES_H_
#define _ALL_TYPES_H_

/**
 * @brief Parametersatz fuer allgemeine Heizkreise, wie FB und HK.
 */
typedef struct all_tvl_s {
    float steigung;         /**< Heizkreis Heizkurvensteigung                    */
    float niveau;           /**< Heizkreis Heizkurvenparallelverschiebung        */
    float absenk;           /**< Heizkreis Nachtabsenkung in Grad C              */
    float min;              /**< Heizkreis Frostschutztemperatur in Grad C       */
    float max;              /**< Heizkreis maximale Vorlauftemperatur in Grad C  */
} all_tvl_t;

typedef struct all_reg_s {
    float kp;               /**< Regler Verstaerkung PI-Regler in %/K                */
    float ki;               /**< Regler Verstaerkung PI-Regler I-Anteil in %/(K x s) */
    float ap;               /**< Regler Arbeitspunktoffset in %                      */
} all_reg_t;

#endif /* _ALL_TYPES_H_ */
