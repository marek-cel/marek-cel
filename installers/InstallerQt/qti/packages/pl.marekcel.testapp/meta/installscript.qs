function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
  component.createOperations();

  if ( systemInfo.productType === "windows" )
  {
    component.addOperation(
      "CreateShortcut",
      "@TargetDir@/test.exe",
      "@StartMenuDir@/TestApp.lnk",
      "workingDirectory=@TargetDir@",
      "iconPath=@TargetDir@/test.ico",
      "iconId=0",
      "description=TestApp"
    );
  }
}
