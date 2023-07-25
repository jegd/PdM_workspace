/*
 * Header de API_debounce
 *
 * Permite trabajar con la entrada del boton de usuario
 *
 */


void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas

/* La función readKey debe leer una variable interna del módulo y devolver
 *  true o false si la tecla fue presionada.  Si devuelve true,
 *  debe resetear (poner en false) el estado de la variable.
*/
bool readKey();
