
package Printtokens;

import Printtokens.Printtokens;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import org.junit.runners.Parameterized.Parameter;
import java.util.*;
import org.junit.experimental.runners.Enclosed;

@RunWith(Enclosed.class)
public class PrinttokensTest {
      
    public PrinttokensTest() {
    }
    
    public static void main(final String[] args) throws Exception {

    }
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }

    
    public static class IS_OPEN_CHARACTER_STREAM{
        @Test
        public void testOpen_character_stream_noFilename() {
            System.out.println("open_character_stream");
            Printtokens instance = new Printtokens();
            String input = null;
            BufferedReader result = instance.open_character_stream(input);
            
            assertTrue(result!= null);
        }
        
        @Test
        public void testOpen_character_stream_file_present() {
            System.out.println("open_character_stream");
            Printtokens instance = new Printtokens();
            String input = "textfile.txt";
            BufferedReader result = instance.open_character_stream(input);
            
            assertTrue(result!= null);
        }
        
        @Test
        public void testOpen_character_stream_fileDNE() {
            System.out.println("open_character_stream");
            Printtokens instance = new Printtokens();
            String input = "null.txt";
            BufferedReader result = instance.open_character_stream(input);
            
            assertNull(result);
        }
    }
    
  
    public static class IS_OPEN_TOKEN_STREAM{
        @Test
        public void testOpen_token_stream_NOT_NULL() {
            System.out.println("open_token_stream");
            
            Printtokens instance = new Printtokens();
            String input = "textfile.txt";
            BufferedReader result = instance.open_character_stream(input);
            
            assertTrue(result!= null);
        }
        
        @Test
        public void testOpen_token_stream_NULL() {
            System.out.println("open_token_stream");
            
            Printtokens instance = new Printtokens();
            String input = "null.txt";
            BufferedReader result = instance.open_character_stream(input);
            
            assertNull(result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class GET_TOKEN{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
                    {"non.txt", null},
                    {"test1.txt",null},
                    {"test2.txt","["},
                    {"test3.txt","\";"},
                    {"test4.txt","a"},
                    {"test5.txt","\"a\""},
                    {"test6.txt","a"},
                    {"test7.txt","!@#"}
                });
         }
    
        
        @Parameter(0)
        public String input;
        
        @Parameter(1)
        public String expResult;
    
    @Test
    public void testGet_token() {
        System.out.println("get_token");
        Printtokens instance = new Printtokens();
        BufferedReader br = instance.open_token_stream(input);
        String result = instance.get_token(br);
        assertTrue(br != null);
        assertEquals(expResult, result);
   
    }
    
 }
    
    @RunWith(Parameterized.class)
    public static class IS_TOKEN_END{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	    {0,49,false},
            	    {0,59,true},
            	    {0,47,true},
            	    {2,10,true},
            	    {2,49,false}, 
            		{1,10,true},
            		{1,49,false},
            		{0,-1,true}     		       	       	              	       	
                });
         }

        @Parameter(0)
        public int input_str_com_id;
        @Parameter(1)
        public int input_res;
        @Parameter(2)
        public Boolean exp;
        
        @Test
        public void testIs_token_end() {
            System.out.println("is_token_end");
            boolean result = Printtokens.is_token_end(input_str_com_id, input_res);
            assertEquals(exp, result);
        }
    }


    @RunWith(Parameterized.class)
    public static class TOKEN_TYPE{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	    {"!#"},
            	    {";"},
            	    {"adc"},
            	    {"\" JUnit \""},
            	    {"360"}, 
            	    {"1"}, 
            	    {"//"}, 
                    {"has"}                                          
                });
         }
        
        @Parameter(0)
        public String input;
        
        @Test
        public void testToken_type() {
            System.out.println("token_type");
            Printtokens instance = new Printtokens();
            instance.token_type(input);
        }
    }
    
    
    @RunWith(Parameterized.class)
    public static class PRINT_TOKEN{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            		{"!#"},
            		{";"},
            		{"adc"},
            		{"\" JUnit \""},
            		{"360"}, 
            		{"1"}, 
            		{"//"}, 
            		{"has"}    
                });
         }
        
        @Parameter(0)
        public String input;
        
        @Test
        public void testPrint_token() {
            System.out.println("print_token");
            Printtokens instance = new Printtokens();
            instance.print_token(input);

        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_COMMENT{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            		{";", true},
                    {"b", false}
                    
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_comment() {
            System.out.println("is_comment");
            boolean result = Printtokens.is_comment(input);
            assertEquals(exp, result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_KEYWORD{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            		{"or", true},
                    {"adc", false}
                    
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_keyword() {
            System.out.println("is_keyword");
            boolean result = Printtokens.is_keyword(input);
            assertEquals(exp, result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_CHAR_CONSTANT{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	 	{"#bac", true},
                    {"234", false}
                   
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_char_constant() {
            System.out.println("is_char_constant");
            boolean result = Printtokens.is_char_constant(input);
            assertEquals(exp, result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_NUM_CONSTANT{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	 	{"c", false},
            	 	{"1", true},
            	 	{"1cc", false},
                    {"142", true}
                                          
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_num_constant() {
            System.out.println("is_num_constant");
            boolean result = Printtokens.is_num_constant(input);
            assertEquals(exp, result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_STR_CONSTANT{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	 	{"5", false},
            	 	{"\"", true},
            	 	{"\"a", true},
                    {"\"\"", true}                        
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_str_constant() {
            System.out.println("is_str_constant");
            boolean result = Printtokens.is_str_constant(input);
            assertEquals(exp, result);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_IDENTIFIER{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
                	{"234", true},
                	{"b", false},
                    {"b?", false}
                });
         }

        @Parameter(0)
        public String input;
        @Parameter(1)
        public Boolean exp;
        
        @Test
        public void testIs_identifier() {
            System.out.println("is_identifier");
            boolean result = Printtokens.is_identifier(input);
            assertEquals(exp, result);
            
        }
    }
    
    @RunWith(Parameterized.class)
    public static class PRINT_SPEC_SYMBOL{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
                    {"("},
                    {")"},
                    {"["},
                    {"]"},
                    {"/"},          
                    {","},
                    {"`"},
                    {"b"}
                });
         }
        @Parameter(0)
        public String input;
        
        @Test
        public void testPrint_spec_symbol(){
            System.out.println("Print_spec_symbol");
            Printtokens.print_spec_symbol(input);
        }
    }
    
    @RunWith(Parameterized.class)
    public static class IS_SPEC_SYMBOL{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
            	 	{'3', false},
            	 	{',', true},
            	 	{'`', true},
            	 	{'/', true},
            		{']', true},
            	 	{'[', true},
            	    {')', true},
                    {'(', true}                                                             
                });
         }

        @Parameter(0)
        public char is_spec_symbol_char;
        @Parameter(1)
        public Boolean is_spec_symbol_boolean;

        @Test
        public void testIs_spec_symbol() {
            System.out.println("is_spec_symbol");
            boolean result = Printtokens.is_spec_symbol(is_spec_symbol_char);
            assertEquals(is_spec_symbol_boolean, result);
       
        }
    }
    
    @RunWith(Parameterized.class)
    public static class MAIN{
        @Parameters
        public static Iterable<Object[]> data() {
            return Arrays.asList(new Object[][] { 
                    {"-f","textfile.txt"},
                });
         }
        
        @Parameter(0)
        public static String arg1;
        @Parameter(1)
        public static String arg2;
        
      
        @Test
        public void testMain() throws Exception {
            System.out.println("main");
            String[] args = {arg1,arg2};
            main(args);     
        }
        
    }
    
}
