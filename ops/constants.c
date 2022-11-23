#include<string.h>
#include"constants.h"
#include"operations.h"

void init(){
strcpy(OPTPROCESSOR_API, "https://localhost:4430/OptmyzrService.svc/DoWork");
strcpy(OPTPROCESSOR_DBOPS_API, "https://localhost:4430/OptmyzrService.svc/DbWork");
strcpy(OPTPROCESSOR_BING_API, "https://localhost:4430/OptmyzrService.svc/DoBWork");
strcpy(SHOPPINGPROCESSOR_API, "https://localhost:4430/ShoppingService.svc/DoWork");
strcpy(SHOPPINGPROCESSOR_DBOPS_API, "https://localhost:4430/ShoppingService.svc/DbWork");
strcpy(SHOPPINGPROCESSOR_BING_API, "https://localhost:4430/ShoppingService.svc/DoBWork");


strcpy(accs_list_op, "GetAllOptyAccountsListForUser");
strcpy(report_pdf_path, "SubmitDownloadReportTemplateFromS3");
strcpy(report_templates, "ReportingTemplatesList");
strcpy(express_sugg_path, "OptSuggestions");
}