# Vanilla JS Mini‑Apps (No jQuery)

This repo contains **three** small web pages, all linked from a single **Home** page:

1. **Reverse a String** — enter text, see its reverse.
2. **Numeric Palindrome** — enter a series of numbers and check if it’s a palindrome (non‑digits ignored).
3. **Tip Calculator** — enter a bill subtotal and tip %; see tip and total.

All pages share a single `style.css` and `index.js`. No jQuery is used.

## File Structure

```
.
├── index.html        # Home page with instructions + links
├── reverse.html      # Page 1
├── palindrome.html   # Page 2
├── tip.html          # Page 3
├── index.js          # All JavaScript logic
└── style.css         # Shared styles
```

## Run Locally

Just open `index.html` in your browser. No build step needed.

## GitHub Submission (example workflow)

1. Create a new repository on GitHub (e.g., `vanilla-js-mini-apps`).
2. Locally, copy these files into a folder and run:
   ```bash
   git init
   git add .
   git commit -m "Assignment: reverse/palindrome/tip (no jQuery)"
   git branch -M main
   git remote add origin https://github.com/<your-username>/vanilla-js-mini-apps.git
   git push -u origin main
   ```
3. Share:
   - **Repo link:** `https://github.com/<your-username>/vanilla-js-mini-apps`
   - **GitHub Pages URL (optional):** enable GitHub Pages (“Deploy from a branch”, root). Then your site might be at:
     `https://<your-username>.github.io/vanilla-js-mini-apps/`

## Notes

- The reverse function uses `Array.from` to handle emojis and surrogate pairs safely.
- The palindrome check strips all non‑digits before comparing.
- The tip calculator validates input and formats amounts to two decimals.
