# TradeX

**TradeX** is a high-performance command-line matching engine that simulates the core mechanics of a **limit order book**, just like those used in real-world stock exchanges.

---

## 📖 What is TradeX?

TradeX is a terminal-based application that acts as a simplified version of a stock exchange. It lets users place BUY and SELL orders for different stocks. Orders are matched automatically using **price-time priority**, similar to professional trading systems.

---

## 🧠 What is a Matching Engine?

A **matching engine** is the core system of a stock exchange that pairs BUY and SELL orders based on price and time. Its job is to:

- Maintain separate **buy and sell order books** for each stock.
- Match orders whenever the conditions are right.
- Execute full or partial trades.
- Prioritize orders by **better price first**, then by **earlier time**.

TradeX mimics these behaviors accurately with a simple command-line interface.

---

## ⚙️ Features

- ✅ BUY/SELL order support
- ✅ Real-time order matching
- ✅ Per-stock order books
- ✅ Price-time priority
- ✅ Trade execution messages
- ✅ Manual view and help system
- ✅ Rejection of duplicate order IDs
---

## 📦 Setup Instructions

1. Go to the [Releases](https://github.com/yourusername/tradex/releases) section of this repository.
2. Download `tradex.exe`.
3. Run it from your terminal or command prompt:

```bash
./tradex.exe
