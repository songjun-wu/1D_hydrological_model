The repository contains a 1D model that can simulate simultaneously hydrological fluxes and tracers.

To compile the model, simply direct to folder release_linux and make. An execute will be created.

The model needs basic GIS setting and climatic inputs. They should be located respectively in folder spatial and climate. Since this model is only limited to 1D, all spatial files are formalised as 3*3 raster. The parameters should also be specified in the same folder.

The climatic inputs are prepared by separately saving the time series of each variable into binary file. Please check the example in two folders.

The model settings can be modified in config.ini -  for instance, specifying the filename of each parameter, or determining which variable to output. An example was given in main folder. This file should be located under the same path of execute.
