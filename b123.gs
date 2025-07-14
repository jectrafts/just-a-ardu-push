function doPost(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var data = JSON.parse(e.postData.contents);

  var b1 = data.b1 || "No value";
  var b2 = data.b2 || "No value";
  var b3 = data.b3 || "No value";

  sheet.getRange("B1").setValue(b1);
  sheet.getRange("B2").setValue(b2);
  sheet.getRange("B3").setValue(b3);

  return ContentService.createTextOutput("Success");
}

function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var b1 = sheet.getRange("B1").getValue();
  var b2 = sheet.getRange("B2").getValue();
  var b3 = sheet.getRange("B3").getValue();

  var result = {
    b1: b1,
    b2: b2,
    b3: b3
  };

  return ContentService
    .createTextOutput(JSON.stringify(result))
    .setMimeType(ContentService.MimeType.JSON);
}
