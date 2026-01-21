import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { Product } from '../../models/product.model';
import { ProductService } from '../../services/product.service';

@Component({
  selector: 'app-review',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './review.component.html',
  styleUrl: './review.component.css'
})
export class ReviewComponent implements OnInit {
  product: Product | null = null;
  loading = false;
  error: string | null = null;
  orderMessage: string | null = null;
  submitting = false;

  constructor(
    private productService: ProductService,
    private router: Router
  ) {}

  ngOnInit(): void {
    this.loadSelectedProduct();
  }

  loadSelectedProduct(): void {
    const local = this.productService.getSelectedProductLocal();
    if (local) {
      this.product = local;
      return;
    }

    this.loading = true;
    this.productService.getSelectedProductFromApi().subscribe({
      next: (product: Product) => {
        this.product = product;
        this.loading = false;
      },
      error: () => {
        this.error = 'No selected product found.';
        this.loading = false;
      }
    });
  }

  onSubmitOrder(): void {
    if (!this.product) {
      this.error = 'No product selected.';
      return;
    }

    this.submitting = true;
    this.error = null;
    this.orderMessage = null;

    const order = {
      productId: this.product.id,
      productName: this.product.name,
      price: this.product.price,
      createdAt: new Date().toISOString()
    };

    this.productService.submitOrder(order).subscribe({
      next: (res: { message: string }) => {
        this.orderMessage = res.message;
        this.submitting = false;
      },
      error: () => {
        this.error = 'Failed to submit order.';
        this.submitting = false;
      }
    });
  }

  backToProducts(): void {
    this.router.navigate(['/']);
  }
}
