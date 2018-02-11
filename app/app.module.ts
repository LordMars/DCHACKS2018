import { BrowserModule } from '@angular/platform-browser';
import { HttpModule } from '@angular/http';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { MdButtonModule, MdInputModule, MdListModule, MdToolbarModule, MdIconModule, MdSnackBarModule } from '@angular/material';
import {MdIconRegistry} from '@angular/material';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {DomSanitizer} from '@angular/platform-browser';
import {FlexLayoutModule} from '@angular/flex-layout';
import { MdCardModule } from '@angular/material';
import { MaterialModule } from '@angular/material';
import { RouterModule, Routes} from '@angular/router';




import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { MainComponent } from './main/main.component';

const appRoutes: Routes = [

	{path: '',component: HomeComponent},
	{path: '',component: MainComponent}
]


@NgModule({
  declarations: [
    AppComponent,
	HomeComponent,
	MainComponent,
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
