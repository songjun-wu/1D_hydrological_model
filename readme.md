The repository contains a 1D model that can simulate simultaneously hydrological fluxes and tracers. It is developped bsaed on EcoHydroPlot by Stevenson et al., 2023.

To compile the model, simply direct to folder release_linux and make. An execute will be created. Note the compilation should be operated on Linux.

*******************************
The model needs basic GIS setting and climatic inputs. They should be located respectively in folder data/spatial and data/climate. Since this model is only limited to 1D, all spatial files are formalised as 3*3 raster. The parameters should also be specified in the same folder. 
The climatic inputs are prepared by separately saving the time series of each variable into binary file.
The model settings can be modified in config.ini -  for instance, specifying the filename of each parameter, or determining which variable to output.

*******************************
An example is given in ./example/main_dev.py. The script automatically compliles the model, generate 100 random parameter samples, runs with the samples, and saves the outputs. 
The example is part of the modelling experiment in Wu et al., in review, where soil moisture and soil water isotopes at 3 depths under 4 vegetation covers in catchment Demnizter Millcreek are calibrated.
The observation data (soil moisture and soil water isotopes) are given in ./data/obs.csv
The GIS inputs are given in ./data/spatial
The readable climate inputs are given in ./data/input.csv, while the binary version as model inputs are in ./data/climate
The configs for the 4 vegetation covers are given in ./data/configs

Reference:
Stevenson, J., Birkel, C., Comte, J.-C., Tetzlaff, D., Marx, C., Neill, A., et al. (2023). Quantifying heterogeneity in ecohydrological partitioning in urban green spaces through the integration of empirical and modelling approaches. Environmental Monitoring and Assessment, 195, 468. https://doi.org/10.1007/s10661-023-11055-6
Wu, S., Tetzlaff, D., Soulsby, C. Revising common approaches for calibration: insights from a 1-D hydrological model with high-dimensional parameters and objectives. Water Resources Research, in reivew