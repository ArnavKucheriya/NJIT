const express = require("express");
const cors = require("cors");

const app = express();
app.use(cors());
app.use(express.json());

// Endpoint to count vowels & consonants
app.post("/analyze", (req, res) => {
    const text = req.body.text.toLowerCase();
    const vowelsList = "aeiou";
    let vowels = 0, consonants = 0;

    for (let ch of text) {
        if (/[a-z]/.test(ch)) {
            if (vowelsList.includes(ch)) vowels++;
            else consonants++;
        }
    }

    res.json({ vowels, consonants });
});

app.listen(3000, () => console.log("Server running on port 3000"));
