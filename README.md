# Projeto Integrador UNIVESP — Monitoramento de Falhas no Pavimento Asfáltico em São Carlos-SP

Plataforma inteligente e de baixo custo baseada em Internet das Coisas (*IoT*) para identificação, classificação por severidade e georreferenciamento de descontinuidades viárias (buracos e desníveis) em São Carlos-SP.

---

## 📌 Visão Geral do Sistema

O sistema captura vibrações e impactos verticais no veículo através da amostragem contínua de aceleração no **Eixo $Z$** combinada às coordenadas de geolocalização do módulo GPS. Os dados são processados localmente pelo microcontrolador **ESP32**, salvos com redundância local em cartão **Micro SD** e transmitidos via Wi-Fi/HTTP para a plataforma **ThingSpeak**. Uma interface gráfica interativa hospedada no **GitHub Pages** permite visualizar espacialmente os pontos de impacto mapeados no município.

---

## 📟 Hardware & Firmware Embarcado

A arquitetura do protótipo é composta por:
- **Microcontrolador:** ESP32 DevKit v1 (processamento local e conectividade Wi-Fi/HTTP).
- **Acelerômetro Triaxial:** ADXL345 (comunicação via barramento $I^2C$, amostragem focada no eixo vertical $Z$).
- **Módulo de Geolocalização:** GPS NEO-6M (comunicação via UART para captura de latitude e longitude).
- **Armazenamento Redundante Local:** Módulo leitor Micro SD (comunicação SPI, garantindo tolerância a falhas em áreas de sombreamento de sinal Wi-Fi).

### Estrutura de Arquivos de Firmware (`/firmware`)
- `teste_sensores.ino`: Script de bancada para calibração do acelerômetro ADXL345 e teste do barramento $I^2C$.
- `gps_coleta.ino`: Script de validação da leitura de sentenças NMEA e fixação de coordenadas com o GPS NEO-6M.
- `main_coleta_telemetria.ino`: Firmware principal integrado (leitura de aceleração no Eixo $Z$, filtragem de ruído, registro local em Micro SD e transmissão de pacotes via requisição HTTP POST para o ThingSpeak).

---

## ☁️ Processamento e Telemetria em Nuvem (ThingSpeak & MATLAB)

Os dados transmitidos alimentam o **Canal 3366928** no ThingSpeak.

### Estrutura de Scripts (`/matlab`)
- `configuracao.txt`: Parâmetros de rede, mapeamento dos campos do canal e chaves de API (*API Keys*).
- `interpretacao.m`: Script em MATLAB responsável por:
  1. Leitura das séries temporais de aceleração vertical no eixo $Z$.
  2. Filtragem e categorização dos picos de impacto conforme limiares de severidade previamente calibrados.
  3. Geração de mapas de calor, histogramas e gráficos de severidade temporal/espacial.

---

## 📊 Classificação dos Impactos no Eixo Z

A severidade dos impactos capturados no eixo vertical ($Z$) é categorizada segundo os limiares de aceleração:

| Categoria | Faixa de Aceleração Vertical ($m/s^2$) | Equivalência Acelerométrica ($g$) | Descrição Técnica |
| :---: | :---: | :---: | :--- |
| **1 — Pequeno** | $11{,}00 \text{ a } 15{,}99 \; m/s^2$ | $\sim 1{,}12 \text{ a } 1{,}63 \; g$ | Irregularidade leve ou pequeno desgaste superficial. |
| **2 — Médio** | $16{,}00 \text{ a } 20{,}99 \; m/s^2$ | $\sim 1{,}63 \text{ a } 2{,}14 \; g$ | Impacto perceptível de severidade intermediária. |
| **3 — Grande** | $\ge 21{,}00 \; m/s^2$ | $\ge \sim 2{,}14 \; g$ | Impacto severo (buracos acentuados ou desníveis graves). |

---

## 🌐 Interface Web Interativa (GitHub Pages)

A visualização cartográfica é disponibilizada publicamente via **GitHub Pages** utilizando a biblioteca **Leaflet.js**:
- **Arquivo principal:** `index.html` (localizado em `/docs` ou na raiz do repositório).
- **Recursos da Interface:**
  - Carregamento e renderização dinâmica dos pontos georreferenciados.
  - Marcadores com código de cores por severidade: **Amarelo** (Pequeno), **Laranja** (Médio) e **Vermelho** (Grande).
  - Pop-ups informativos com data, hora, coordenadas e intensidade registrada.
  - Legendas explicativas e enquadramento automático de mapa (*fitBounds*).
- **Link do Mapa Interativo:** https://projetointegradorsaocarlosgrupo003.github.io/falhas_pavimento/

---

## 📂 Estrutura do Repositório

```text
falhas_pavimento/
├── docs/
│   └── index.html                # Interface gráfica do mapa interativo (GitHub Pages)
├── firmware/
│   ├── teste_sensores.ino        # Validação do acelerômetro ADXL345
│   ├── gps_coleta.ino            # Validação do módulo GPS NEO-6M
│   └── main_coleta_telemetria.ino # Firmware principal integrado (ESP32 + SD + Wi-Fi)
├── matlab/
│   ├── interpretacao.m           # Script de análise e classificação no ThingSpeak
│   └── configuracao.txt          # Configurações de canal e chaves de API
├── LICENSE                       # Licença de código aberto (MIT)
└── README.md                     # Documentação principal do projeto
