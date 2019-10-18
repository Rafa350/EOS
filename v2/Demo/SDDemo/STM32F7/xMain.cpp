extern void AppMain();
extern void InitializeHardware();


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

	// Inicialitzacio del hardware
	//
	InitializeHardware();

	// Inicia l'aplicacio EOS
	//
	AppMain();

	return 0;
}
