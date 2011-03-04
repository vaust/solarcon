#ifndef _REG_H_
#define _REG_H_

#include "gen_types.h"

/* <Konstanten> */
#define REG_STATEVARS 4
/* <Konstanten/> */

/* <Typen> */
/**
 * @brief Struktur mit allen Parameter des Reglers
 */
typedef struct reg_par_s {
    float TA;               /**< Abtastzeit                           */
    float kp;               /**< Proportionalbeiwert                  */
    float ki;               /**< Integralbeiwert                      */
    float ap;               /**< Arbeitspunkt des Reglers             */
    float lower_limit;      /**< Untere Begrenzung des Reglerausgangs */
    float upper_limit;      /**< Obere  Begrenzung des Reglerausgangs */
} reg_par_t;

/**
 * @brief Klassendefinition des Reglers
 *
 * Die Eingangs- und Ausgangsgroessen sind als Pointer auf die Groessen der uebergeordneten,
 * den Regler anwendenden Komponente angelegt.
 */
typedef struct reg_class_s {
    reg_par_t   p;                    /**< Parametersatz des PI-Reglers   */
    float       *y;                   /**< Pointer auf Stellgroesse zum Zeitpunkt t   */
    float       *soll;                /**< Pointer auf Sollwert zum Zeitpunkt t       */
    float       *ist;                 /**< Pointer auf Istwert zum Zeitpunkt t        */
    float       x[REG_STATEVARS];     /**< Zustandsgroessen fuer Blockdarstellung des Anti Windup PI-Reglers */
} reg_class_t;

/* <Typen> */

/* <Prototypen> */
float reg_Limit( float value, const float lower_limit, const float upper_limit );
void reg_PI_Init(       reg_class_t *self,
                  const float        TA,
                  const float        kp,
                  const float        ki,
                  const float        ap,
                  const float        lower_limit,
                  const float        upper_limit,
                        float       *y,
                        float       *soll,
                        float       *ist      );

float reg_PI_Run( reg_class_t *self );
/* <Prototypen/> */

#endif /* _SUP_H_ */




