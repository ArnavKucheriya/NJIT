const express = require("express");
const cors = require("cors");

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(express.json());

// In-memory data
const products = [
  {
    id: 1,
    name: "Wireless Headphones",
    price: 79.99,
    image: "/assets/headphones.webp",
    description: "Comfortable wireless headphones with clear sound."
  },
  {
    id: 2,
    name: "Gaming Mouse",
    price: 49.99,
    image: "/assets/products/mouse.jpg",
    description: "High precision gaming mouse with RGB lighting."
  },
  {
    id: 3,
    name: "Mechanical Keyboard",
    price: 99.99,
    image: "/assets/products/keyboard.jpg",
    description: "Mechanical keyboard with tactile switches."
  },
  {
    id: 4,
    name: "4K Monitor",
    price: 299.99,
    image: "/assets/products/monitor.jpg",
    description: "27-inch 4K monitor with thin bezels."
  }
];

// Store last selected product in memory
let selectedProduct = null;

// 1. GET /api/products
app.get("/api/products", (req, res) => {
  res.json(products);
});

// 2. POST /api/select-product
app.post("/api/select-product", (req, res) => {
  // Store selected product
  selectedProduct = req.body;
  res.json({ message: "Product selected" });
});

// 3. GET /api/selected-product
app.get("/api/selected-product", (req, res) => {
  if (!selectedProduct) {
    return res
      .status(404)
      .json({ message: "No product selected yet" });
  }
  res.json(selectedProduct);
});

// 4. POST /api/submit-order
app.post("/api/submit-order", (req, res) => {
  const orderData = req.body;
  console.log("Order received:", orderData);

  res.json({ message: "Your item will be delivered soon." });
});

app.listen(PORT, () => {
  console.log(`Backend API running on http://localhost:${PORT}`);
});
