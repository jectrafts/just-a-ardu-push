

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
