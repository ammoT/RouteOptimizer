# 🚀 RouteOptimizer  
Uno strumento da terminale scritto in **C++17** che calcola il percorso più efficiente tra due punti di partenza (A e B) e una destinazione finale, utilizzando:

- **Google Geocoding API** → converte indirizzi in coordinate  
- **Google Routes Matrix API** → calcola distanze reali su strada  
- **Tabella ASCII elegante** → mostra i risultati in modo chiaro e leggibile  

Perfetto per esercitarsi con API REST, cURL, JSON parsing e formattazione CLI.

---

## ✨ Funzionalità

- Inserisci **indirizzi reali** (es. “Via Roma 10, Torino”, “Duomo Milano”)
- Conversione automatica in **latitudine/longitudine**
- Calcolo delle distanze:
  - A → Dest
  - B → Dest
  - A → B → Dest
  - B → A → Dest
- Evidenziazione del percorso migliore
- Tabella ASCII professionale e allineata
- Gestione errori API (REQUEST_DENIED, ZERO_RESULTS, ecc.)

---

## 📦 Requisiti

- macOS / Linux / Windows (con cURL installato)
- Google Cloud API Key con:
  - **Geocoding API** abilitata
  - **Routes API** abilitata
- Librerie:
  - `curl`
  - `nlohmann/json`

Installazione su macOS:

```bash
brew install curl
brew install nlohmann-json
