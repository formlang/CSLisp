OutputDir:=nugets
DeployDir:=nuget-packages

ProjectNames:=$(basename $(Projects))
Nugets:=$(addsuffix .nupkg,$(ProjectNames))

%.nupkg:
	@echo "Build $@"
ifndef Config
	@echo "Please provide the config with Config=debug or Config=release"
else
ifeq ($(Config),Release)
	@echo "Output release version"
	dotnet pack $(addsuffix .csproj,$(basename $@)) --output $(OutputDir) --configuration Release
else
	@echo "Output debug version"
	dotnet pack $(addsuffix .csproj,$(basename $@)) --include-symbols --output $(OutputDir)
endif
endif


build: $(Nugets)
	@echo "********************************"
	@echo "Build done"
	@echo "********************************"

pre-build:
	@echo "Create nugets dir"
	@mkdir nugets
	@echo "Done"

deploy: 
	@echo "********************************"
	@mv $(OutputDir)/*.nupkg $(DeployDir)/
	@echo "Deploy done"
	@echo "********************************"

publish:
	cd $(DeployDir) && git add *.nupkg && git commit -m 'k'

clean:
	@echo "Delete nugets"
	if [ -d nugets ]; then \
	  rm -rf nugets; \
        fi 
	@echo "Done"

.PHONY: build pre-build clean deploy publish
