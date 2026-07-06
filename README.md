# Projeto3-Supervisorio-Qt
# Projeto 3: Sistema de Aquisição e Supervisão de Dados (Qt/C++)

Este repositório contém a implementação dos módulos **Cliente Produtor** e **Cliente Consumidor** para um sistema supervisório de dados via rede (TCP/IP). O projeto foi desenvolvido em **C++** utilizando o framework **Qt** (via Qt Creator), como parte da avaliação da disciplina de Programação Avançada.

O sistema simula um ambiente de aquisição de dados, onde máquinas geram medições (Produtor) que são enviadas a um roteador central (Servidor), e posteriormente lidas e plotadas graficamente por uma central de monitoramento (Consumidor).

## 🏗️ Arquitetura do Sistema

O projeto é composto por três módulos que se comunicam através da porta TCP `1234`:

1. **Servidor TCP** *(Fornecido pelo professor)*: Atua como o roteador de mensagens. Recebe os dados gerados, armazena em memória e responde às requisições de listagem e envio.
2. **Cliente Produtor** *(Implementado)*: Conecta-se ao servidor e envia medições aleatórias de tempo e valor (simulando um sensor) com base em limites de máximo/mínimo configuráveis.
3. **Cliente Consumidor** *(Implementado)*: Conecta-se ao servidor, lista os IPs dos produtores ativos e desenha um gráfico dinâmico em tempo real das últimas 30 amostras geradas pela máquina selecionada.

---

## ✨ Funcionalidades Implementadas

### Módulo Produtor
- Conexão e desconexão com IP dinâmico.
- Botões `Put` (iniciar envio) e `Stop` (parar envio).
- Sliders para controle dinâmico do **Valor Mínimo** e **Valor Máximo** dos dados gerados.
- Slider de **Timing** para controlar o intervalo (em segundos) entre os envios dos dados.

### Módulo Consumidor
- Conexão e desconexão com IP dinâmico.
- Botão `Update` para requisitar e listar os IPs dos produtores ativos na rede.
- Seleção de máquina específica através de um `QListWidget`.
- Botões `Start` e `Stop` para controlar a leitura dos dados.
- Slider de **Timing** para ajustar o intervalo de requisição dos dados.
- **Gráfico Customizado (Classe Plotter):** Um widget promovido, construído do zero, que ajusta automaticamente a escala (X e Y) e plota as linhas ligando os pontos de dados recebidos dinamicamente no evento de pintura (`paintEvent`).

---

## 📸 Demonstração Visual

*(Professor, abaixo estão as telas do sistema em funcionamento integrado)*

### Visão Geral do Sistema (Servidor, Produtor e Consumidor)
![Visão Geral](coloque-aqui-o-link-do-seu-print-com-as-3-telas.jpg)

### Detalhe do Gráfico (Consumidor)
![Gráfico Consumidor](coloque-aqui-o-link-do-seu-print-do-grafico-tracando.jpg)

---

## 🚀 Como Compilar e Executar o Projeto

### Pré-requisitos
- **Qt Creator** instalado (versão baseada em Qt 5 ou Qt 6).
- Compilador C++ (MinGW no Windows, ou GCC/Clang no Linux/macOS).
- Módulo Servidor compilado e em execução.

### Passo a Passo

1. **Inicie o Servidor:**
   Abra e rode o executável do Servidor fornecido pelo repositório original da disciplina. Uma tela preta de terminal se abrirá escutando na porta 1234.

2. **Compilando o Cliente Produtor:**
   - Abra o Qt Creator.
   - Vá em `File > Open File or Project...` e selecione o arquivo `CMakeLists.txt` dentro da pasta do **Produtor**.
   - Aceite a configuração padrão (Configure Project).
   - Clique no botão **Run** (Seta verde) ou pressione `Ctrl + R`.

3. **Compilando o Cliente Consumidor:**
   - Repita o processo acima, mas agora selecionando o arquivo `CMakeLists.txt` na pasta do **Consumidor**.

4. **Operando o Sistema (Fluxo de Teste):**
   - **No Produtor:** Insira o IP `127.0.0.1` e clique em *Connect*. Ajuste os limites (Min/Max) e o tempo (Timing). Clique em *Put*. O servidor mostrará os dados chegando.
   - **No Consumidor:** Insira o IP `127.0.0.1` e clique em *Connect*. Clique em *Update* para listar a máquina local. Clique no IP que aparecer na lista, ajuste o Slider de *Timing* para determinar a velocidade de leitura e clique em *Start*.
   - O gráfico ganhará vida, traçando a linha azul das últimas 30 amostras geradas!

---
*Desenvolvido com 💻 e ☕ por [SEU NOME AQUI] - UFRN*
