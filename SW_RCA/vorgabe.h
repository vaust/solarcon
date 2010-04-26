#ifndef VORGABE_H
#define VORGABE_H

/* Vorgabewerte: */
#define ALL_Tau_mittel_Zeit		  36	/* Zeit über die die Außentemperatur gemittelt wird (in Stunden) 	*/
#define MAX_ALL_Tau_mittel_Zeit   48    /* max. Wert aus Kommentar in vorgaben.ini                                            */		
#define ALL_Partydauer		   	 120  	/* Fußbodenheizkreis Dauer der Betriebsverlängerung (in Minuten)  	*/
#define ALL_Frostschutz			  30	/* Außentemperatur unter der Heizkreis immer in Betrieb	in 1/10 °C	*/
#define ALL_AT_Start			 150	/* Außentemperatur unter der Heizung startet in 1/10 °C          	*/

#define SOL_dT_ein_SW			  70	/* Einschalt-Differenztemperatur für Solarpumpe und Speicherabsperrventile  in 1/10 °C */
#define SOL_dT_aus_SW			  35	/* Ausschalt-Differenztemperatur für Solarpumpe und Speicherabsperrventile  in 1/10 °C */
#define SOL_KOLL_T_max			1250    /* Max. Kollektortemperatur in 1/10 °C 		*/
#define SOL_SP_T_max			1100	/* Max. Speichertemperatur in 1/10 °C  		*/
#define SOl_SP1_T_min			 500	/* Min. Temperatur Speicher 1 in 1/10 °C 	*/

#define KES_SP_dT_SW			 100 	/* Temperaturdifferenz zwischen Kessel- und Speicher-SW in 1/10 °C */

#define	HK_Tvl_Steigung			  1.4	/* Heizkörperheizkreis Heizkurvensteigung                	  	*/
#define HK_Tvl_Niveau			  0.0	/* Heizkörperheizkreis Heizkurvenparallelverschiebung    	  	*/
#define HK_Tvl_Absenk			 100    /* Heizkörperheizkreis Nachtabsenkung in 1/10 °C              	*/
#define HK_Tvl_Min				 100	/* Heizkörperheizkreis Frostschutztemperatur in 1/10 °C       	*/
#define HK_Tvl_Max				 750	/* Heizkörperheizkreis maximale Vorlauftemperatur in 1/10 °C  	*/
#define HK_Frostschutz			  30	/* Außentemperatur ab der Heizkreis in Betrieb ist in 1/10 °C 	*/
#define HK_REG_Kp				  1.0	/* Heizkörperheizkreis Verstärkung PI-Regler in %/K       		*/
#define HK_REG_Tn				  1.0	/* Heizkörperheizkreis Nachstellzeit PI-Regler in Minuten 		*/
#define HK_Tr_SW                 205    /* Heizkörperheizkreis Raumtemperatur Sollwert                  */

#define FB_Tvl_Steigung			  0.7	/* Fußbodenheizkreis Heizkurvensteigung  					*/
#define FB_Tvl_Niveau			 20.0	/* Fußbodenheizkreis Heizkurven Parallelverschiebung 		*/
#define FB_Tr_SW				 205	/* Fußbodenheizkreis Raumtemperatursollwert in 1/10 °C  	*/
#define FB_Tvl_Absenk			 100    /* Fußbodenheizkreis Nachtabsenkung in 1/10 °C           	*/
#define FB_Tvl_Min				 100	/* Fußbodenheizkreis Frostschutztemperatur in 1/10 °C   	*/
#define FB_Tvl_Max				 350	/* Fußbodenheizkreis max. Vorlauftemperatur in 1/10 °C  	*/

#define FB_REG_Kp				  1.0	/* Fußbodenheizkreis Verstärkung PI-Regler in %/K       	*/
#define FB_REG_Tn				  1.0	/* Fußbodenheizkreis Nachstellzeit PI-Regler in Minuten 	*/

#define WW_Tww_SW				 400	/* Warmwasser-Temperatur-Sollwert in 1/10 °C				*/
#define WW_Tww_Max				 600	/* Warmwasser-Maximaltemperatur	in 1/10 °C 					*/
#define WZ_Faktor				  1.0	/* Wärmezähler auf Pumpenstellbefehl						*/
#define Wz_Max					 25.0	/* Max. Warmwasserdurchfluß in l/min						*/

#define WW_HZG_REG_Kp			  1.0	/* Heizungs-VL-Temperatur-Regelung Verstärkung Kp       	*/
#define WW_HZG_REG_Tn			  1.0	/* Heizungs-VL-Temperatur-Regelung Nachlaufzeit Tn      	*/
#define WW_Tww_Tvl_Faktor		  1.0	/* Einfluß der WW-Temperatur auf die Heizungs-VL-Temp.  	*/
#define WW_Tz_SW				 400	/* Temperatursollwert des Zirkulationswassers in 1/10 °C	*/

/* Variablendefinitionen für Vorgabe Variablen, initialisiert in init_variables() */

#ifdef _INIT_VAR_C_
    #define _EXT_ 
#else
    #define _EXT_ extern
#endif

_EXT_ int all_tau_mittel_zeit;		/* Zeit über die die Außentemperatur gemittelt wird (in Stunden) 	*/
_EXT_ int all_partydauer;		   	/* Fußbodenheizkreis Dauer der Betriebsverlängerung (in Minuten)  	*/
_EXT_ int all_frostschutz;		  	/* Außentemperatur unter der Heizkreis immer in Betrieb	in 1/10 °C	*/
_EXT_ int all_at_start;		 		/* Außentemperatur unter der Heizung startet in 1/10 °C          	*/

_EXT_ int sol_dt_ein_sw;		    /* Einschalt-Differenztemperatur für Solarpumpe und Speicherabsperrventile  in 1/10 °C */
_EXT_ int sol_dt_aus_sw;		    /* Ausschalt-Differenztemperatur für Solarpumpe und Speicherabsperrventile  in 1/10 °C */
_EXT_ int sol_koll_t_max;			/* Max. Kollektortemperatur in 1/10 °C 		*/
_EXT_ int sol_sp_t_max;				/* Max. Speichertemperatur in 1/10 °C  		*/
_EXT_ int sol_sp1_t_min;		 	/* Min. Temperatur Speicher 1 in 1/10 °C 	*/

_EXT_ int kes_sp_dt_sw;		  		/* Temperaturdifferenz zwischen Kessel- und Speicher-SW in 1/10 °C */

_EXT_ float hk_tvl_steigung;		/* Heizkörperheizkreis Heizkurvensteigung                	  	*/
_EXT_ float hk_tvl_niveau;	  		/* Heizkörperheizkreis Heizkurvenparallelverschiebung    	    */
_EXT_ int hk_tvl_absenk;		 	/* Heizkörperheizkreis Nachtabsenkung in 1/10 °C              	*/
_EXT_ int hk_tvl_min;			 	/* Heizkörperheizkreis Frostschutztemperatur in 1/10 °C       	*/
_EXT_ int hk_tvl_max;			 	/* Heizkörperheizkreis maximale Vorlauftemperatur in 1/10 °C    */
_EXT_ int hk_frostschutz;		  	/* Außentemperatur ab der Heizkreis in Betrieb ist in 1/10 °C 	*/
_EXT_ float hk_reg_kp;		  		/* Heizkörperheizkreis Verstärkung PI-Regler in %/K       	    */
_EXT_ float hk_reg_tn;		  		/* Heizkörperheizkreis Nachstellzeit PI-Regler in Minuten 	    */
_EXT_ int hk_tr_sw;                 /* Heizkörperheizkreis Raumtemperatur Sollwert                  */

_EXT_ float fb_tvl_steigung;	  	/* Fußbodenheizkreis Heizkurvensteigung  		                */
_EXT_ float fb_tvl_niveau;	 		/* Fußbodenheizkreis Heizkurven Parallelverschiebung 		    */
_EXT_ int fb_tr_sw;			 		/* Fußbodenheizkreis Raumtemperatursollwert in 1/10 °C  	    */
_EXT_ int fb_tvl_absenk;		    /* Fußbodenheizkreis Nachtabsenkung in 1/10 °C           	    */
_EXT_ int fb_tvl_min;			 	/* Fußbodenheizkreis Frostschutztemperatur in 1/10 °C   	    */
_EXT_ int fb_tvl_max;			 	/* Fußbodenheizkreis max. Vorlauftemperatur in 1/10 °C  	    */

_EXT_ float fb_reg_kp;		  		/* Fußbodenheizkreis Verstärkung PI-Regler in %/K       	    */
_EXT_ float fb_reg_tn;		  		/* Fußbodenheizkreis Nachstellzeit PI-Regler in Minuten 	    */

_EXT_ int ww_tww_sw;			 	/* Warmwasser-Temperatur-Sollwert in 1/10 °C			    */
_EXT_ int ww_tww_max;			 	/* Warmwasser-Maximaltemperatur	in 1/10 °C 		            */
_EXT_ float wz_faktor;		  		/* Wärmezähler auf Pumpenstellbefehl				        */
_EXT_ float wz_max;			 		/* Max. Warmwasserdurchfluß in l/min				        */

_EXT_ float ww_hzg_reg_kp;		 	/* Heizungs-VL-Temperatur-Regelung Verstärkung Kp       	*/
_EXT_ float ww_hzg_reg_tn;			/* Heizungs-VL-Temperatur-Regelung Nachlaufzeit Tn      	*/
_EXT_ float ww_tww_tvl_faktor;  	/* Einfluß der WW-Temperatur auf die Heizungs-VL-Temp.  	*/
_EXT_ int ww_tz_sw;			 		/* Temperatursollwert des Zirkulationswassers in 1/10 °C	*/

#endif


