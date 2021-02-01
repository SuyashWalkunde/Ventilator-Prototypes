void inspiratory_pressure( void *pvParameters );
void expiratory_pressure( void *pvParameters );

void inspiratory_flow_rate( void *pvParameters );
void expiratory_flow_rate( void *pvParameters );

void display_get_data( void *pvParameters );

void CPAP( void *pvParameters );
void CPAPGraph(void *pvParameters);

void BiPAP( void *pvParameters );
void BiPAPGraph(void *pvParameters);
void CMV( void *pvParameters );
void SIMV_PC(void *pvParameters );

int give_extra_breath(float inhale, float exhale, float breaths_per_minute, float pressure);
