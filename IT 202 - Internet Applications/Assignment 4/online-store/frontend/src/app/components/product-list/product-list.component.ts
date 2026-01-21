import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { Product } from '../../models/product.model';
import { ProductService } from '../../services/product.service';

@Component({
  selector: 'app-product-list',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './product-list.component.html',
  styleUrl: './product-list.component.css'
})
export class ProductListComponent implements OnInit {
  products: Product[] = [];
  loading = false;
  error: string | null = null;

  constructor(
    private productService: ProductService,
    private router: Router
  ) {}

  ngOnInit(): void {
    this.loadProducts();
  }

  loadProducts(): void {
    this.loading = true;
    this.error = null;

    this.productService.getProducts().subscribe({
      next: (products: Product[]) => {
        this.products = products;
        this.loading = false;
      },
      error: () => {
        this.error = 'Failed to load products.';
        this.loading = false;
      }
    });
  }

  onBuy(product: Product): void {
    this.productService.selectProduct(product).subscribe({
      next: () => {
        this.router.navigate(['/review']);
      },
      error: () => {
        this.error = 'Failed to select product.';
      }
    });
  }
}
