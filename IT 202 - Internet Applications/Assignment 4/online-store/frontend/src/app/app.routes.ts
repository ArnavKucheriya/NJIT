import { Routes } from '@angular/router';
import { ProductListComponent } from './components/product-list/product-list.component';
import { ReviewComponent } from './components/review/review.component';

export const routes: Routes = [
  { path: '', component: ProductListComponent },
  { path: 'review', component: ReviewComponent },
  { path: '**', redirectTo: '' }
];
