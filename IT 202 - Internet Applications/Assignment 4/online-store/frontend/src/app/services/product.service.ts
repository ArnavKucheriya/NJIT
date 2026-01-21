import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, tap } from 'rxjs';
import { Product } from '../models/product.model';

@Injectable({
  providedIn: 'root'
})
export class ProductService {
  private apiUrl = 'http://localhost:3000/api';
  private selectedProduct: Product | null = null;

  constructor(private http: HttpClient) {}

  getProducts(): Observable<Product[]> {
    return this.http.get<Product[]>(`${this.apiUrl}/products`);
  }

  selectProduct(product: Product): Observable<any> {
    this.selectedProduct = product;
    return this.http.post(`${this.apiUrl}/select-product`, product).pipe(
      tap(() => {})
    );
  }

  getSelectedProductLocal(): Product | null {
    return this.selectedProduct;
  }

  getSelectedProductFromApi(): Observable<Product> {
    return this.http.get<Product>(`${this.apiUrl}/selected-product`);
  }

  submitOrder(orderData: any): Observable<{ message: string }> {
    return this.http.post<{ message: string }>(
      `${this.apiUrl}/submit-order`,
      orderData
    );
  }
}
