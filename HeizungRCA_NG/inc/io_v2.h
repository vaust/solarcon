#ifndef _IO_V2_H_
#define _IO_V2_H_

#define IO_MAX_TEMP    850.0
#define IO_MIN_TEMP   -100.0

/* <Typen> */
typedef enum io_obj_status_e { obj_Normal,             /**< Sensorwert ist innerhalb der Messbereichsgrenzen und gueltig */
                               obj_Kabelbruch,         /**< Es liegt eine Kabelbruch vor */
                               obj_Kurzschluss,        /**< Der Sensor ist kurzgeschlossen */
                               obj_Unplausibel,        /**< Der Temperaturwert ist unplausibel */
                               obj_AllgemeinerFehler,  /**< Es liegt ein allgemeiner, nicht naeher spezifizierter Fehler vor */
                               obj_ManuelleZuweisung   /**< Der Messwert kann in de Diagnose manuell zugewiesen werden */
                              } io_obj_status_t;

typedef io_tempsens_obj_s {
    float           messbereich_anfang;
    float           messbereich_ende;
    // float           aufloesung;
    float           messwert;
    io_obj_status_t status;
    temp10_pt1000_t *kbus_adresse_p;
} io_tempsens_obj_t;

typedef io_digin_obj_s {
    di_bitbyte_t    messwert;
    io_obj_status_t status;
} io_digin_obj_t;
    
/* </Typen> */

/* <Variablen> */
#ifdef _IO_V2_C_
    #define PUBLIC
#else
    #define PUBLIC extern const
#endif

PUBLIC io_tempsens_obj_t    io_ALL_Tau_MW;
PUBLIC io_tempsens_obj_t    io_SOL_KOLL_T_MW;
PUBLIC io_tempsens_obj_t    io_SOL_SP1_Tu_MW;
PUBLIC io_tempsens_obj_t    io_SOL_SP1_To_MW;
PUBLIC io_tempsens_obj_t    io_SOL_SP2_Tu_MW;
PUBLIC io_tempsens_obj_t    io_SOL_SP2_To_MW;
PUBLIC io_tempsens_obj_t    io_KES_Tvl_MW;
PUBLIC io_tempsens_obj_t    io_KES_Trl_MW;
PUBLIC io_tempsens_obj_t    io_HK_Tvl_MW;
PUBLIC io_tempsens_obj_t    io_HK_Trl_MW;
PUBLIC io_tempsens_obj_t    io_FB_PRIM_Trl_MW;
PUBLIC io_tempsens_obj_t    io_FB_SEK_Tvl_MW;
PUBLIC io_tempsens_obj_t    io_WW_HZG_Tvl_MW;
PUBLIC io_tempsens_obj_t    io_WW_HZG_Trl_MW;
PUBLIC io_tempsens_obj_t    io_WW_Tww_MW;
/* </Variablen> */

/* <Prototypen> */
void io_InitAllTempSens( void );
float io_Temp( io_tempsens_obj_t *this );
/* </Prototypen> */

#endif /* _IO_V2_H_ */


