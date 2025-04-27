#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define pino_Sensor A0

/* Porcentagem de umidade mínima para iniciar a irrigação */
int Valor_Critico = 45;
int ValAnalogIn;
String msg;
int linha;

/* Cria o objeto de controle para o display OLED. */
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);

  /* Inicializa o display OLED com o endereço 0x3C. */
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha na alocação do SSD1306"));
    for (;;)
      ;  
  }

  display.clearDisplay();
  tela_inicial();
}

void loop() {
  /* Realiza a leitura do sensor e armazena o valor na variável ValAnalogIn */
  ValAnalogIn = analogRead(pino_Sensor);

  /* Converte o valor analógico para porcentagem */
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);

  // Exibe no monitor serial
  Serial.print("Umidade: ");
  Serial.print(Porcento);
  Serial.println("%");

  // Atualiza o display OLED
  display.clearDisplay();
  tela_inicial();  // Redesenha o cabeçalho

  // Exibe a umidade no display
  display.setCursor(4, 20);
  display.setTextSize(2);
  display.print(Porcento);
  display.print("%");

  // Exibe o status
  display.setTextSize(1);
  display.setCursor(4, 40);
  if (Porcento <= Valor_Critico) {
    display.print("Umidade baixa!");
    Serial.println("Umidade baixa!");
  } else {
    display.print("Umidade Adequada");
    Serial.println("Umidade Adequada...");
  }

  display.display();
  delay(2000);  // Aguarda 2 segundos entre as leituras
}

void tela_inicial() {
  display.drawRect(0, 0, 128, 64, 1);
  display.drawFastHLine(0, 14, 128, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4, 4);
  display.print("UMIDADE DO SOLO");
}