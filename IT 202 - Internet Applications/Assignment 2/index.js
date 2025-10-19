// Reverse a string
document.addEventListener("DOMContentLoaded", function () {
  const reverseForm = document.getElementById("reverseForm");
  if (reverseForm) {
    reverseForm.addEventListener("submit", function (e) {
      e.preventDefault();
      const input = document.getElementById("reverseInput").value;
      const reversed = input.split("").reverse().join("");
      document.getElementById("reverseResult").textContent = "Reversed: " + reversed;
    });
  }

  // Palindrome checker
  const palForm = document.getElementById("palForm");
  if (palForm) {
    palForm.addEventListener("submit", function (e) {
      e.preventDefault();
      const input = document.getElementById("palInput").value.replace(/\s+/g, "");
      const reversed = input.split("").reverse().join("");
      const result = input === reversed ? "It is a palindrome!" : "Not a palindrome.";
      document.getElementById("palResult").textContent = result;
    });
  }

  // Tip calculator
  const tipForm = document.getElementById("tipForm");
  if (tipForm) {
    tipForm.addEventListener("submit", function (e) {
      e.preventDefault();
      const subtotal = parseFloat(document.getElementById("subtotal").value);
      const tipPercent = parseFloat(document.getElementById("tipPercent").value);

      if (isNaN(subtotal) || isNaN(tipPercent)) {
        document.getElementById("tipResult").textContent = "Please enter valid numbers.";
        return;
      }

      const tip = subtotal * (tipPercent / 100);
      const total = subtotal + tip;

      document.getElementById("tipResult").textContent =
        `Tip: $${tip.toFixed(2)} | Total: $${total.toFixed(2)}`;
    });
  }
});
