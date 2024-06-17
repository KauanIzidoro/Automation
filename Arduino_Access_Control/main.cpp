#include <LiquidCrystal.h>

// Conexão física nos pinos
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const int rows[] = {6, 7, 8, 9};
const int cols[] = {10, 11, 12, 13};

// Mapear o teclado
const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Variáveis Globais
String password = "";
String input = "";
String admpass = "";
String adminput = "";
bool access_state = false;

// Criar um Administrador
void setAdmin()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Admin Pass: ");
  adminput = "";
  keyboard_input();
  lcd.setCursor(6, 1);
  lcd.print(hiden_password(adminput));
  admpass = adminput;
  adminput = "";
  input = "";
}

void setup()
{
  // Inicialização do display LCD
  lcd.begin(16, 2);

  // Inicialização do teclado matricial
  for (int i = 0; i < 4; i++)
  {
    pinMode(rows[i], INPUT_PULLUP);
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], HIGH);
  }

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Access Control");
  lcd.setCursor(2, 1);
  lcd.print("IZIDORO LTDA");
  delay(2000);
  lcd.clear();
  setAdmin();
  menu();
}

void loop()
{
  // Chama a função que verifica e retorna se alguma tecla for pressionada
  char key = keyboardScan();
  // Se retornar 0/nulo, não tem tecla pressionada
  if (key > 0)
  {
    if (access_state)
    {
      Login(key);
    }
    else
    {
      notLogin(key);
    }
  }
}

void notLogin(char key)
{
  if (key == '#')
  {
    if (input == password || input == admpass)
    {
      access_state = true;
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("ACCESS");
      delay(2000);
      lcd.clear();
      menu();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("TRY AGAIN");
      delay(2000);
      lcd.clear();
      input = "";
      menu();
    }
  }
  else if (key == '*')
  {
    input = "";
    lcd.clear();
    menu();
  }
  else
  {
    input += key;
    lcd.setCursor(6, 1);
    lcd.print(hiden_password(input));
  }
}

void Login(char key)
{
  switch (key)
  {
  case 'A':
    lcd.clear();
    lcd.print("Enter pass:");
    input = "";
    keyboard_input();
    password = input;
    input = "";
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("SUCCESS");
    delay(4000);
    lcd.clear();
    menu();
    break;
  case 'B':
    input = "";
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("DELETED");
    password = "";
    delay(4000);
    lcd.clear();
    menu();
    break;
  case 'C':
    lcd.clear();
    lcd.print("Password: ");
    lcd.setCursor(0, 1);
    lcd.print(password);
    delay(4000);
    lcd.clear();
    menu();
    break;
  case 'D':
    access_state = false;
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("LOGOFF");
    input = "";
    delay(2000);
    lcd.clear();
    menu();
    break;
  }
}

void keyboard_input()
{
  char key;
  while ((key = keyboardScan()) != '#')
  {
    if (key)
    {
      adminput += key;
      lcd.setCursor(6, 1);
      lcd.print(hiden_password(adminput));
    }
  }
}

void menu()
{
  if (access_state)
  {
    lcd.setCursor(0, 0);
    lcd.print("A: New password");
    lcd.setCursor(0, 1);
    lcd.print("B: Del. password");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("C: Show password");
    lcd.setCursor(0, 1);
    lcd.print("D: Logoff");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("New Password: ");
    lcd.setCursor(6, 1);
    lcd.print(hiden_password(input));
  }
}

char keyboardScan()
{
  // Retorno da função - padrão retorna nulo
  char scan = 0;
  for (int i = 0; i < 4; i++)
  {
    // Colocar o pino de saída (coluna) em nível lógico baixo
    digitalWrite(cols[i], LOW);
    // Verificar em todas as entradas (linhas)
    // Se tem algum sinal em nível lógico baixo (botão pressionado)
    for (int j = 0; j < 4; j++)
    {
      // Verificar se tem sinal nos pinos de entrada (linhas) em nível lógico baixo
      if (digitalRead(rows[j]) == LOW)
      {
        scan = keys[j][i];
        // Esperar a tecla ser solta para evitar múltiplas leituras
        while (digitalRead(rows[j]) == LOW)
        {
          delay(10);
        }
      }
    }
    // Colocar o pino de saída (coluna) em nível lógico alto
    digitalWrite(cols[i], HIGH);
  }
  // Retorno da função
  return scan;
}

String hiden_password(String input)
{
  String masked = "****";
  for (int i = 0; i < input.length() && i < 4; i++)
  {
    masked[i] = input[i];
  }
  return masked;
}

//mostrar a senha desaparecendo a cada 1s.
//mostrar '****' piscando;
//quando escrito o '*' nao pisca mais.
