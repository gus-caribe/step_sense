#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int trigger=2, echo=3, motorFrente=8, motorBaixo=9;
int frente = 0, baixo = 0, estavaFrente = 0, estavaBaixo = 0, distanciaFrenteCm;

void setup()
{
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	pinMode(motorFrente, OUTPUT);
	pinMode(motorBaixo, OUTPUT);
	lox.begin(0x31);
}

void loop()
{
	//Atribuição de valor às variáveis da leitura anterior:

	estavaFrente = frente;
	estavaBaixo = baixo;

	//Leitura do sensor ultrassônico:

	pinMode(trigger, OUTPUT);
	digitalWrite(trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);
	pinMode(echo, INPUT);
	distanciaFrenteCm = pulseIn(echo, HIGH) * 0.01723;

	//Classificação das distâncias:

	if (distanciaFrenteCm > 30)
		frente = 3;
	else if (distanciaFrenteCm >= 20)
		frente = 2;
	else if (distanciaFrenteCm >= 10)
		frente = 1;
	else
		frente = 0;

	//Leitura do sensor a laser:

	VL53L0X_RangingMeasurementData_t measure;
	lox.rangingTest (&amp; measure);

	if(measure.RangeStatus != 4)
	baixo = measure.RangeMilliMeter;

	//Comandos:

	//Frente:

	if (frente == 3 &amp;&amp; estavaFrente != frente)//se mudou de lugar para mais de 30cm
	{
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
	}
	else if (frente == 2 &amp;&amp; estavaFrente != frente)//se mudou de lugar para entre 20cm e 30cm
	{
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
		delay(100);
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
	}
	else if (frente == 1 &amp;&amp; estavaFrente != frente)//se mudou de lugar para entre 10cm e 20cm
	{
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
		delay(100);
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
		delay(100);
		digitalWrite(motorFrente, HIGH);
		delay(100);
		digitalWrite(motorFrente, LOW);
	}
	else if (frente == 0 &amp;&amp; estavaFrente != frente)//se mudou de lugar para menos de 10cm
	{
		digitalWrite(motorFrente, HIGH);
		delay(1000);
		digitalWrite(motorFrente, LOW);
	}

	//Baixo:

	if (baixo > estavaBaixo + 50)//se mudaram 50mm abruptamente
	{
		digitalWrite(motorBaixo, HIGH);
		delay(1000);
		digitalWrite(motorBaixo, LOW);
	}
}
