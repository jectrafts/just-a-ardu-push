function doPost(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var data = JSON.parse(e.postData.contents);

  // This writes the value to cell B1
  var value = data.value || "No value";
  sheet.getRange("B1").setValue(value);

  return ContentService.createTextOutput("Success");
}
